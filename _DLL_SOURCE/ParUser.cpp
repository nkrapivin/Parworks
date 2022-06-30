#include "Par.h"
#include "ParGM.h"
#include <string>

funcdef(ParUser_GetHSteamUser) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetHSteamUser()
	};
}

funcdef(ParUser_BLoggedOn) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BLoggedOn()
	};
}

funcdef(ParUser_GetSteamID) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetSteamID().ConvertToUint64()
	};
}

funcdef(ParUser_InitiateGameConnection_DEPRECATED) {
	ensureiptr(SteamUser());
	ensureargc(6);
	ensurekind(0, eRVK_PTR);
	ensurekind(2, eRVK_INT64);

	Result = RValue{
		SteamUser()->InitiateGameConnection_DEPRECATED(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetInt32(argument, 1),
			CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 2)) },
			ParGM()->YYGetUint32(argument, 3),
			parcast<unsigned short>(ParGM()->YYGetInt32(argument, 4)),
			ParGM()->YYGetBool(argument, 5)
		)
	};
}

funcdef(ParUser_TerminateGameConnection_DEPRECATED) {
	ensureiptr(SteamUser());
	ensureargc(2);

	SteamUser()->TerminateGameConnection_DEPRECATED(
		ParGM()->YYGetUint32(argument, 0),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 1))
	);
}

funcdef(ParUser_TrackAppUsageEvent) {
	ensureiptr(SteamUser());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);

	if (argument_count > 2) {
		ensurekind(2, eRVK_STRING);
	}

	SteamUser()->TrackAppUsageEvent(
		CGameID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)) },
		ParGM()->YYGetInt32(argument, 1),
		(argument_count > 2) ? ParGM()->YYGetString(argument, 2) : ""
	);
}

funcdef(ParUser_GetUserDataFolder) {
	ensureiptr(SteamUser());
	ensurekind(0, eRVK_OBJECT);

	uint32 siz{ ParGM()->YYGetUint32(argument, 1) };
	std::string tmpbuff{ };
	tmpbuff.resize(siz);

	bool ok{
		SteamUser()->GetUserDataFolder(
			cparcast<char*>(tmpbuff.data()),
			siz
		)
	};

	ParGM()->StructAddString(&argument[0], "refval", tmpbuff.c_str());

	Result = RValue{ ok };
}

funcdef(ParUser_StartVoiceRecording) {
	ensureiptr(SteamUser());

	SteamUser()->StartVoiceRecording();
}

funcdef(ParUser_StopVoiceRecording) {
	ensureiptr(SteamUser());

	SteamUser()->StopVoiceRecording();
}

funcdef(ParUser_GetAvailableVoice) {
	ensureiptr(SteamUser());
	ensureargc(1);
	ensurekind(0, eRVK_OBJECT);

	uint32 ncompressed{ 0 };
	uint32 ucompressed{ 0 };

	EVoiceResult res{
		SteamUser()->GetAvailableVoice(
			&ncompressed,
			(argument_count > 1) ? &ucompressed : nullptr,
			(argument_count > 2) ? ParGM()->YYGetUint32(argument, 2) : 0
		)
	};

	ParGM()->StructAddDouble(&argument[0], "refval", parcast<double>(ncompressed));
	if (argument_count > 1) {
		ensurekind(1, eRVK_OBJECT);
		ParGM()->StructAddDouble(&argument[1], "refval", parcast<double>(ucompressed));
	}

	Result = RValue{ res };
}

funcdef(ParUser_GetVoice) {
	ensureiptr(SteamUser());
	ensureargc(4);
	ensurekind(3, eRVK_OBJECT);

	uint32 nbyteswritten{ 0 };
	uint32 ndecomwritten{ 0 };

	if (argument_count > 5) {
		ensurekind(5, eRVK_PTR);
	}
 
	EVoiceResult res{
		SteamUser()->GetVoice(
			ParGM()->YYGetBool(argument, 0),
			ParGM()->YYGetPtr(argument, 1),
			ParGM()->YYGetUint32(argument, 2),
			&nbyteswritten, // 3
			(argument_count > 4) ? ParGM()->YYGetBool(argument, 4) : false,
			(argument_count > 5) ? ParGM()->YYGetPtr(argument, 5) : nullptr,
			(argument_count > 6) ? ParGM()->YYGetUint32(argument, 6) : 0,
			(argument_count > 7) ? &ndecomwritten : nullptr, // 7
			(argument_count > 8) ? ParGM()->YYGetUint32(argument, 8) : 0
		)
	};

	ParGM()->StructAddDouble(&argument[3], "refval", parcast<double>(nbyteswritten));
	if (argument_count > 7) {
		ensurekind(7, eRVK_OBJECT);
		ParGM()->StructAddDouble(&argument[7], "refval", parcast<double>(ndecomwritten));
	}

	Result = RValue{ res };
}

funcdef(ParUser_DecompressVoice) {
	ensureiptr(SteamUser());
	ensureargc(6);
	ensurekind(0, eRVK_PTR);
	ensurekind(2, eRVK_PTR);
	ensurekind(4, eRVK_OBJECT);

	uint32 written{ 0 };
	EVoiceResult res{
		SteamUser()->DecompressVoice(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetUint32(argument, 1),
			ParGM()->YYGetPtr(argument, 2),
			ParGM()->YYGetUint32(argument, 3),
			&written,
			ParGM()->YYGetUint32(argument, 5)
		)
	};

	ParGM()->StructAddDouble(&argument[4], "refval", parcast<double>(written));
	Result = RValue{ res };
}

funcdef(ParUser_GetVoiceOptimalSampleRate) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetVoiceOptimalSampleRate()
	};
}

funcdef(ParUser_GetAuthSessionTicket) {
	ensureiptr(SteamUser());
	ensureargc(3);
	ensurekind(0, eRVK_PTR);
	ensurekind(2, eRVK_OBJECT);

	uint32 cbticket{ 0 };
	HAuthTicket tk{
		SteamUser()->GetAuthSessionTicket(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetInt32(argument, 1),
			&cbticket
		)
	};

	ParGM()->StructAddDouble(&argument[2], "refval", parcast<double>(cbticket));
	Result = RValue{ tk };
}

funcdef(ParUser_BeginAuthSession) {
	ensureiptr(SteamUser());
	ensureargc(1);
	ensurekind(0, eRVK_PTR);
	ensurekind(2, eRVK_INT64);

	Result = RValue{
		SteamUser()->BeginAuthSession(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetInt32(argument, 1),
			CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 2)) }
		)
	};
}

funcdef(ParUser_EndAuthSession) {
	ensureiptr(SteamUser());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	SteamUser()->EndAuthSession(
		CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)) }
	);
}

funcdef(ParUser_CancelAuthTicket) {
	ensureiptr(SteamUser());
	ensureargc(1);

	SteamUser()->CancelAuthTicket(
		ParGM()->YYGetUint32(argument, 0)
	);
}

funcdef(ParUser_UserHasLicenseForApp) {
	ensureiptr(SteamUser());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamUser()->UserHasLicenseForApp(
			CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)) },
			ParGM()->YYGetUint32(argument, 1)
		)
	};
}

funcdef(ParUser_BIsBehindNAT) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BIsBehindNAT()
	};
}

funcdef(ParUser_AdvertiseGame) {
	ensureiptr(SteamUser());
	ensureargc(3);
	ensurekind(0, eRVK_INT64);

	SteamUser()->AdvertiseGame(
		CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)) },
		ParGM()->YYGetUint32(argument, 1),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2))
	);
}

funcdef(ParUser_RequestEncryptedAppTicket) {
	ensureiptr(SteamUser());
	ensureargc(2);
	ensurekind(0, eRVK_PTR);

	Result = RValue{
		SteamUser()->RequestEncryptedAppTicket(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetInt32(argument, 1)
		)
	};
}

funcdef(ParUser_GetEncryptedAppTicket) {
	ensureiptr(SteamUser());
	ensureargc(3);
	ensurekind(0, eRVK_PTR);
	ensurekind(2, eRVK_OBJECT);

	uint32 ticketSize{ 0 };

	bool ok{
		SteamUser()->GetEncryptedAppTicket(
			ParGM()->YYGetPtr(argument, 0),
			ParGM()->YYGetInt32(argument, 1),
			&ticketSize
		)
	};

	ParGM()->StructAddDouble(&argument[2], "refval", parcast<double>(ticketSize));

	Result = RValue{ ok };
}

funcdef(ParUser_GetGameBadgeLevel) {
	ensureiptr(SteamUser());
	ensureargc(2);

	Result = RValue{
		SteamUser()->GetGameBadgeLevel(
			ParGM()->YYGetInt32(argument, 0),
			ParGM()->YYGetBool(argument, 1)
		)
	};
}

funcdef(ParUser_GetPlayerSteamLevel) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetPlayerSteamLevel()
	};
}

funcdef(ParUser_RequestStoreAuthURL) {
	ensureiptr(SteamUser());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamUser()->RequestStoreAuthURL(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParUser_BIsPhoneVerified) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BIsPhoneVerified()
	};
}

funcdef(ParUser_BIsTwoFactorEnabled) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BIsTwoFactorEnabled()
	};
}

funcdef(ParUser_BIsPhoneIdentifying) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BIsPhoneIdentifying()
	};
}

funcdef(ParUser_BIsPhoneRequiringVerification) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->BIsPhoneRequiringVerification()
	};
}

funcdef(ParUser_GetMarketEligibility) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetMarketEligibility()
	};
}

funcdef(ParUser_GetDurationControl) {
	ensureiptr(SteamUser());

	Result = RValue{
		SteamUser()->GetDurationControl()
	};
}

funcdef(ParUser_BSetDurationControlOnlineState) {
	ensureiptr(SteamUser());
	ensureargc(1);

	Result = RValue{
		SteamUser()->BSetDurationControlOnlineState(
			parcast<EDurationControlOnlineState>(
				ParGM()->YYGetInt32(argument, 0)
			)
		)
	};
}

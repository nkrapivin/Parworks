#include "Par.h"
#include "ParGM.h"

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

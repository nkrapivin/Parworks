#include "Par.h"
#include "ParGM.h"
#include <string>

funcdef(ParUtils_GetSecondsSinceAppActive) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetSecondsSinceAppActive()
	};
}

funcdef(ParUtils_GetSecondsSinceComputerActive) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetSecondsSinceComputerActive()
	};
}

funcdef(ParUtils_GetConnectedUniverse) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetConnectedUniverse()
	};
}

funcdef(ParUtils_GetServerRealTime) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetServerRealTime()
	};
}

funcdef(ParUtils_GetIPCountry) {
	ensureiptr(SteamUtils());

	ParGM()->YYCreateString(
		&Result,
		SteamUtils()->GetIPCountry()
	);
}

funcdef(ParUtils_GetImageSize) {
	ensureiptr(SteamUtils());
	ensureargc(3);
	ensurekind(1, eRVK_OBJECT);
	ensurekind(2, eRVK_OBJECT);

	uint32 w{ 0 }, h{ 0 };
	bool ok{
		SteamUtils()->GetImageSize(
			ParGM()->YYGetInt32(argument, 0),
			&w,
			&h
		)
	};

	ParGM()->StructAddDouble(&argument[1], "refval", parcast<double>(w));
	ParGM()->StructAddDouble(&argument[2], "refval", parcast<double>(h));

	Result = RValue{ ok };
}

funcdef(ParUtils_GetImageRGBA) {
	ensureiptr(SteamUtils());
	ensureargc(3);
	ensurekind(1, eRVK_PTR);

	Result = RValue{
		SteamUtils()->GetImageRGBA(
			ParGM()->YYGetInt32(argument, 0),
			parcast<uint8*>(ParGM()->YYGetPtr(argument, 1)),
			ParGM()->YYGetInt32(argument, 2)
		)
	};
}

funcdef(ParUtils_GetCurrentBatteryPower) {
	ensureiptr(SteamUtils());

	Result = RValue{
		parcast<int>(SteamUtils()->GetCurrentBatteryPower())
	};
}

funcdef(ParUtils_GetAppID) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetAppID()
	};
}

funcdef(ParUtils_SetOverlayNotificationPosition) {
	ensureiptr(SteamUtils());
	ensureargc(1);

	SteamUtils()->SetOverlayNotificationPosition(
		parcast<ENotificationPosition>(ParGM()->YYGetInt32(argument, 0))
	);
}

funcdef(ParUtils_IsAPICallCompleted) {
	ensureiptr(SteamUtils());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_OBJECT);

	bool failed{ false };
	bool ok{
		SteamUtils()->IsAPICallCompleted(
			parcast<SteamAPICall_t>(ParGM()->YYGetInt64(argument, 0)),
			&failed
		)
	};

	ParGM()->StructAddBool(&argument[1], "refval", failed);
	Result = RValue{ ok };
}

funcdef(ParUtils_GetAPICallFailureReason) {
	ensureiptr(SteamUtils());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamUtils()->GetAPICallFailureReason(
			parcast<SteamAPICall_t>(ParGM()->YYGetInt64(argument, 0))
		)
	};
}

funcdef(ParUtils_GetAPICallResult) {
	ensureiptr(SteamUtils());
	ensureargc(5);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_PTR);
	ensurekind(4, eRVK_OBJECT);

	bool failed{ false };
	bool ok{
		SteamUtils()->GetAPICallResult(
			parcast<SteamAPICall_t>(ParGM()->YYGetInt64(argument, 0)),
			ParGM()->YYGetPtr(argument, 1),
			ParGM()->YYGetInt32(argument, 2),
			ParGM()->YYGetInt32(argument, 3),
			&failed
		)
	};

	ParGM()->StructAddBool(&argument[4], "refval", failed);

	Result = RValue{ ok };
}

funcdef(ParUtils_GetIPCCallCount) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetIPCCallCount()
	};
}

static int _SetWarningMessageHookIndex{ -1 };
static void _WarningMessageHook(int nSeverity, const char* pchDebugText) {
	if (_SetWarningMessageHookIndex < 0) {
		return;
	}
	
	RValue res{ };
	std::array<RValue, 3> args{ RValue{ _SetWarningMessageHookIndex }, RValue{ nSeverity }, RValue{ } };

	ParGM()->YYCreateString(
		&args[2],
		pchDebugText
	);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

funcdef(ParUtils_SetWarningMessageHook) {
	ensureiptr(SteamUtils());
	ensureargc(1);

	_SetWarningMessageHookIndex = ParGM()->YYGetInt32(argument, 0);

	SteamUtils()->SetWarningMessageHook(
		(_SetWarningMessageHookIndex < 0)
		? nullptr
		: &_WarningMessageHook
	);
}

funcdef(ParUtils_IsOverlayEnabled) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsOverlayEnabled()
	};
}

funcdef(ParUtils_BOverlayNeedsPresent) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->BOverlayNeedsPresent()
	};
}

funcdef(ParUtils_CheckFileSignature) {
	ensureiptr(SteamUtils());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamUtils()->CheckFileSignature(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParUtils_ShowGamepadTextInput) {
	ensureiptr(SteamUtils());
	ensureargc(5);
	ensurekind(2, eRVK_STRING);
	ensurekind(4, eRVK_STRING);

	Result = RValue{
		SteamUtils()->ShowGamepadTextInput(
			parcast<EGamepadTextInputMode>(ParGM()->YYGetInt32(argument, 0)),
			parcast<EGamepadTextInputLineMode>(ParGM()->YYGetInt32(argument, 1)),
			ParGM()->YYGetString(argument, 2),
			ParGM()->YYGetUint32(argument, 3),
			ParGM()->YYGetString(argument, 4)
		)
	};
}

funcdef(ParUtils_GetEnteredGamepadTextLength) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetEnteredGamepadTextLength()
	};
}

funcdef(ParUtils_GetEnteredGamepadTextInput) {
	ensureiptr(SteamUtils());
	ensureargc(2);
	ensurekind(0, eRVK_OBJECT);

	uint32_t mysiz{ ParGM()->YYGetUint32(argument, 1) };

	std::string outputBuffer{ "" };
	outputBuffer.resize(mysiz);

	bool ok{
		SteamUtils()->GetEnteredGamepadTextInput(
			cparcast<char*>(outputBuffer.data()),
			mysiz
		)
	};

	ParGM()->StructAddString(&argument[0], "refval", outputBuffer.c_str());
	Result = RValue{ ok };
}

funcdef(ParUtils_GetSteamUILanguage) {
	ensureiptr(SteamUtils());

	ParGM()->YYCreateString(
		&Result,
		SteamUtils()->GetSteamUILanguage()
	);
}

funcdef(ParUtils_IsSteamRunningInVR) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsSteamRunningInVR()
	};
}

funcdef(ParUtils_SetOverlayNotificationInset) {
	ensureiptr(SteamUtils());
	ensureargc(2);

	SteamUtils()->SetOverlayNotificationInset(
		ParGM()->YYGetInt32(argument, 0),
		ParGM()->YYGetInt32(argument, 1)
	);
}

funcdef(ParUtils_IsSteamInBigPictureMode) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsSteamInBigPictureMode()
	};
}

funcdef(ParUtils_StartVRDashboard) {
	ensureiptr(SteamUtils());

	SteamUtils()->StartVRDashboard();
}

funcdef(ParUtils_IsVRHeadsetStreamingEnabled) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsVRHeadsetStreamingEnabled()
	};
}

funcdef(ParUtils_SetVRHeadsetStreamingEnabled) {
	ensureiptr(SteamUtils());
	ensureargc(1);

	SteamUtils()->SetVRHeadsetStreamingEnabled(
		ParGM()->YYGetBool(argument, 0)
	);
}

funcdef(ParUtils_IsSteamChinaLauncher) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsSteamChinaLauncher()
	};
}

funcdef(ParUtils_InitFilterText) {
	ensureiptr(SteamUtils());

	if (argument_count < 1 || argument[0].typeOf() == eRVK_UNDEFINED) {
		Result = RValue{
			SteamUtils()->InitFilterText()
		};
	}
	else {
		Result = RValue{
			SteamUtils()->InitFilterText(
				ParGM()->YYGetUint32(argument, 0)
			)
		};
	}
}

funcdef(ParUtils_FilterText) {
	ensureiptr(SteamUtils());
	ensureargc(5);
	ensurekind(1, eRVK_INT64);
	ensurekind(2, eRVK_STRING);
	ensurekind(3, eRVK_OBJECT);

	uint32_t mysiz{ ParGM()->YYGetUint32(argument, 4) };

	std::string outputText{ "" };
	outputText.resize(mysiz);

	int l{
		SteamUtils()->FilterText(
			parcast<ETextFilteringContext>(ParGM()->YYGetInt32(argument, 0)),
			CSteamID{ parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 1)) },
			ParGM()->YYGetString(argument, 2),
			cparcast<char*>(outputText.data()),
			mysiz
		)
	};

	ParGM()->StructAddString(&argument[3], "refval", outputText.c_str());
	Result = RValue{ l };
}

funcdef(ParUtils_GetIPv6ConnectivityState) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->GetIPv6ConnectivityState(
			parcast<ESteamIPv6ConnectivityProtocol>(
				ParGM()->YYGetInt32(argument, 0)
			)
		)
	};
}

funcdef(ParUtils_IsSteamRunningOnSteamDeck) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->IsSteamRunningOnSteamDeck()
	};
}

funcdef(ParUtils_ShowFloatingGamepadTextInput) {
	ensureiptr(SteamUtils());
	ensureargc(5);

	Result = RValue{
		SteamUtils()->ShowFloatingGamepadTextInput(
			parcast<EFloatingGamepadTextInputMode>(ParGM()->YYGetInt32(argument, 0)),
			ParGM()->YYGetInt32(argument, 1),
			ParGM()->YYGetInt32(argument, 2),
			ParGM()->YYGetInt32(argument, 3),
			ParGM()->YYGetInt32(argument, 4)
		)
	};
}

funcdef(ParUtils_SetGameLauncherMode) {
	ensureiptr(SteamUtils());
	ensureargc(1);

	SteamUtils()->SetGameLauncherMode(
		ParGM()->YYGetBool(argument, 0)
	);
}

funcdef(ParUtils_DismissFloatingGamepadTextInput) {
	ensureiptr(SteamUtils());

	Result = RValue{
		SteamUtils()->DismissFloatingGamepadTextInput()
	};
}

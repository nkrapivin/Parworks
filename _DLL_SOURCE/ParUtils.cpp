#include "Par.h"
#include "ParGM.h"
#include <string>

funcdef(ParUtils_ShowGamepadTextInput) {
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
	Result = RValue{
		SteamUtils()->GetEnteredGamepadTextLength()
	};
}

funcdef(ParUtils_GetEnteredGamepadTextInput) {
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
	ParGM()->YYCreateString(
		&Result,
		SteamUtils()->GetSteamUILanguage()
	);
}

funcdef(ParUtils_IsSteamRunningInVR) {
	Result = RValue{
		SteamUtils()->IsSteamRunningInVR()
	};
}

funcdef(ParUtils_SetOverlayNotificationInset) {
	ensureargc(2);

	SteamUtils()->SetOverlayNotificationInset(
		ParGM()->YYGetInt32(argument, 0),
		ParGM()->YYGetInt32(argument, 1)
	);
}

funcdef(ParUtils_IsSteamInBigPictureMode) {
	Result = RValue{
		SteamUtils()->IsSteamInBigPictureMode()
	};
}

funcdef(ParUtils_StartVRDashboard) {
	SteamUtils()->StartVRDashboard();
}

funcdef(ParUtils_IsVRHeadsetStreamingEnabled) {
	Result = RValue{
		SteamUtils()->IsVRHeadsetStreamingEnabled()
	};
}

funcdef(ParUtils_SetVRHeadsetStreamingEnabled) {
	ensureargc(1);

	SteamUtils()->SetVRHeadsetStreamingEnabled(
		ParGM()->YYGetBool(argument, 0)
	);
}

funcdef(ParUtils_IsSteamChinaLauncher) {
	Result = RValue{
		SteamUtils()->IsSteamChinaLauncher()
	};
}

funcdef(ParUtils_InitFilterText) {
	ensureargc(1);

	Result = RValue{
		SteamUtils()->InitFilterText(
			ParGM()->YYGetUint32(argument, 0)
		)
	};
}

funcdef(ParUtils_FilterText) {
	ensureargc(5);
	ensurekind(1, eRVK_INT64);
	ensurekind(2, eRVK_STRING);
	ensurekind(3, eRVK_OBJECT);

	long long stmid{ ParGM()->YYGetInt64(argument, 1) };
	uint32_t mysiz{ ParGM()->YYGetUint32(argument, 4) };

	std::string outputText{ "" };
	outputText.resize(mysiz);

	int l{
		SteamUtils()->FilterText(
			parcast<ETextFilteringContext>(ParGM()->YYGetInt32(argument, 0)),
			CSteamID{ *rparcast<uint64*>(&stmid) },
			ParGM()->YYGetString(argument, 2),
			cparcast<char*>(outputText.data()),
			mysiz
		)
	};

	ParGM()->StructAddString(&argument[3], "refval", outputText.c_str());
	Result = RValue{ l };
}

funcdef(ParUtils_GetIPv6ConnectivityState) {
	Result = RValue{
		SteamUtils()->GetIPv6ConnectivityState(
			parcast<ESteamIPv6ConnectivityProtocol>(ParGM()->YYGetInt32(argument, 0))
		)
	};
}

funcdef(ParUtils_IsSteamRunningOnSteamDeck) {
	Result = RValue{
		SteamUtils()->IsSteamRunningOnSteamDeck()
	};
}

funcdef(ParUtils_ShowFloatingGamepadTextInput) {
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
	ensureargc(1);

	SteamUtils()->SetGameLauncherMode(
		ParGM()->YYGetBool(argument, 0)
	);
}

funcdef(ParUtils_DismissFloatingGamepadTextInput) {
	Result = RValue{
		SteamUtils()->DismissFloatingGamepadTextInput()
	};
}

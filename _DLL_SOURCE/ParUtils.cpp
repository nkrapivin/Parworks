#include "Par.h"
#include "ParGM.h"

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

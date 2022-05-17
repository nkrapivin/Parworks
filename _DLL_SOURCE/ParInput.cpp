#include "Par.h"
#include "ParGM.h"
#include <array>
#include <string>

funcdef(ParInput_Init) {
	ensureargc(1);
	
	Result = RValue{
		SteamInput()->Init(
			ParGM()->YYGetBool(argument, 0)
		)
	};
}

funcdef(ParInput_Shutdown) {
	Result = RValue{
		SteamInput()->Shutdown()
	};
}

funcdef(ParInput_SetInputActionManifestFilePath) {
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->SetInputActionManifestFilePath(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_RunFrame) {
	ensureargc(1);

	SteamInput()->RunFrame(
		ParGM()->YYGetBool(argument, 0)
	);
}

funcdef(ParInput_BWaitForData) {
	ensureargc(2);

	Result = RValue{
		SteamInput()->BWaitForData(
			ParGM()->YYGetBool(argument, 0),
			ParGM()->YYGetUint32(argument, 1)
		)
	};
}

funcdef(ParInput_BNewDataAvailable) {
	Result = RValue{
		SteamInput()->BNewDataAvailable()
	};
}

funcdef(ParInput_GetConnectedControllers) {
	ensureargc(1);
	ensurekind(0, eRVK_ARRAY);

	std::array<InputHandle_t, STEAM_INPUT_MAX_COUNT> c{};
	
	int len{
		SteamInput()->GetConnectedControllers(c.data())
	};

	for (int i{ 0 }; i < len; ++i) {
		RValue tmp{ c[i] };
		ParGM()->SET_RValue(
			&argument[0],
			&tmp,
			nullptr,
			i
		);
	}

	Result = RValue{ len };
}

funcdef(ParInput_EnableDeviceCallbacks) {
	SteamInput()->EnableDeviceCallbacks();
}

static int _EnableActionEventCallbacksFuncScriptIndex{ -1 };
static void _EnableActionEventCallbacksFunc(SteamInputActionEvent_t *pParam) {
	if (_EnableActionEventCallbacksFuncScriptIndex < 0) {
		return;
	}

	RValue Result{ };
	RValue args[2]{ RValue{ _EnableActionEventCallbacksFuncScriptIndex }, RValue{ } };

	RValue _controllerHandle{ pParam->controllerHandle };
	RValue _eEventType{ pParam->eEventType };

	RValue _digitalAction{ };
	RValue _analogAction{ };
	RValue _digitalActionData{ };
	RValue _analogActionData{ };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "controllerHandle", &_controllerHandle);
	ParGM()->StructAddRValue(&args[1], "eEventType", &_eEventType);

	switch (pParam->eEventType) {
		case ESteamInputActionEventType_DigitalAction: {
			RValue _actionHandle{ pParam->digitalAction.actionHandle };

			ParGM()->StructCreate(&_digitalAction);
			ParGM()->StructAddRValue(&_digitalAction, "actionHandle", &_actionHandle);

			ParGM()->StructCreate(&_digitalActionData);
			ParGM()->StructAddBool(&_digitalActionData, "bState", pParam->digitalAction.digitalActionData.bState);
			ParGM()->StructAddBool(&_digitalActionData, "bActive", pParam->digitalAction.digitalActionData.bActive);

			ParGM()->StructAddRValue(&_digitalAction, "digitalActionData", &_digitalActionData);
			break;
		}

		case ESteamInputActionEventType_AnalogAction: {
			RValue _actionHandle{ pParam->analogAction.actionHandle };

			ParGM()->StructCreate(&_analogAction);
			ParGM()->StructAddRValue(&_analogAction, "actionHandle", &_actionHandle);

			ParGM()->StructCreate(&_analogActionData);
			ParGM()->StructAddInt(&_analogActionData, "eMode", pParam->analogAction.analogActionData.eMode);
			ParGM()->StructAddDouble(&_analogActionData, "x", pParam->analogAction.analogActionData.x);
			ParGM()->StructAddDouble(&_analogActionData, "y", pParam->analogAction.analogActionData.y);
			ParGM()->StructAddBool(&_analogActionData, "bActive", pParam->analogAction.analogActionData.bActive);

			ParGM()->StructAddRValue(&_analogAction, "analogActionData", &_analogActionData);
			break;
		}
	}

	ParGM()->StructAddRValue(&args[1], "digitalAction", &_digitalAction);
	ParGM()->StructAddRValue(&args[1], "analogAction", &_analogAction);

	F_ScriptExecute(
		Result,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

funcdef(ParInput_EnableActionEventCallbacks) {
	ensureargc(1);

	_EnableActionEventCallbacksFuncScriptIndex = ParGM()->YYGetInt32(argument, 0);

	SteamInput()->EnableActionEventCallbacks(
		(_EnableActionEventCallbacksFuncScriptIndex < 0)
		? nullptr
		: &_EnableActionEventCallbacksFunc
	);
}

funcdef(ParInput_GetActionSetHandle) {
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetActionSetHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_ActivateActionSet) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);
	
	SteamInput()->ActivateActionSet(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_GetCurrentActionSet) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetCurrentActionSet(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_ActivateActionSetLayer) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->ActivateActionSetLayer(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_DeactivateActionSetLayer) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->DeactivateActionSetLayer(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_DeactivateAllActionSetLayers) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	SteamInput()->DeactivateAllActionSetLayers(
		ParGM()->YYGetInt64(argument, 0)
	);
}

funcdef(ParInput_GetActiveActionSetLayers) {
	ensureargc(1);
	ensurekind(0, eRVK_ARRAY);

	std::array<InputActionSetHandle_t, STEAM_INPUT_MAX_ACTIVE_LAYERS> l{};

	int len{
		SteamInput()->GetActiveActionSetLayers(
			ParGM()->YYGetInt64(argument, 0),
			l.data()
		)
	};

	for (int i{ 0 }; i < len; ++i) {
		RValue tmp{ l[i] };
		ParGM()->SET_RValue(
			&argument[0],
			&tmp,
			nullptr,
			i
		);
	}

	Result = RValue{ len };
}

funcdef(ParInput_GetDigitalActionHandle) {
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetDigitalActionHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_GetDigitalActionData) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	auto acdata{
		SteamInput()->GetDigitalActionData(
			ParGM()->YYGetInt64(argument, 0),
			ParGM()->YYGetInt64(argument, 1)
		)
	};

	ParGM()->StructCreate(&Result);
	ParGM()->StructAddBool(&Result, "bState", acdata.bState);
	ParGM()->StructAddBool(&Result, "bActive", acdata.bActive);
}

funcdef(ParInput_GetDigitalActionOrigins) {
	ensureargc(4);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);
	ensurekind(2, eRVK_INT64);
	ensurekind(3, eRVK_ARRAY);

	std::array<EInputActionOrigin, STEAM_INPUT_MAX_ORIGINS> ors{};
	int l{
		SteamInput()->GetDigitalActionOrigins(
			ParGM()->YYGetInt64(argument, 0),
			ParGM()->YYGetInt64(argument, 1),
			ParGM()->YYGetInt64(argument, 2),
			ors.data()
		)
	};

	for (int i{ 0 }; i < l; ++i) {
		RValue tmp{ ors[i] };
		ParGM()->SET_RValue(
			&argument[3],
			&tmp,
			nullptr,
			i
		);
	}
	
	Result = RValue{ l };
}

funcdef(ParInput_GetStringForDigitalActionName) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForDigitalActionName(
			ParGM()->YYGetInt64(argument, 0)
		)
	);
}

funcdef(ParInput_GetAnalogActionHandle) {
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetAnalogActionHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_GetAnalogActionData) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	auto acdata{
		SteamInput()->GetAnalogActionData(
			ParGM()->YYGetInt64(argument, 0),
			ParGM()->YYGetInt64(argument, 1)
		)
	};

	ParGM()->StructCreate(&Result);
	ParGM()->StructAddInt(&Result, "eMode", acdata.eMode);
	ParGM()->StructAddDouble(&Result, "x", acdata.x);
	ParGM()->StructAddDouble(&Result, "y", acdata.y);
	ParGM()->StructAddBool(&Result, "bActive", acdata.bActive);
}

funcdef(ParInput_GetAnalogActionOrigins) {
	ensureargc(4);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);
	ensurekind(2, eRVK_INT64);
	ensurekind(3, eRVK_ARRAY);

	std::array<EInputActionOrigin, STEAM_INPUT_MAX_ORIGINS> ors{};

	int l{
		SteamInput()->GetAnalogActionOrigins(
			ParGM()->YYGetInt64(argument, 0),
			ParGM()->YYGetInt64(argument, 1),
			ParGM()->YYGetInt64(argument, 2),
			ors.data()
		)
	};

	for (int i{ 0 }; i < l; ++i) {
		RValue tmp{ ors[i] };
		ParGM()->SET_RValue(
			&argument[3],
			&tmp,
			nullptr,
			i
		);
	}

	Result = RValue{ l };
}

static void _AddFilesDirToWhitelist(const char* str) {
	if (!str) {
		return;
	}

	std::string thepath{ str };
	std::size_t lastsepind{ thepath.npos };
	// try both normal slash and backslash
	lastsepind = thepath.find_last_of('/');
	if (lastsepind == thepath.npos) {
		lastsepind = thepath.find_last_of('\\');
	}

	if (lastsepind != thepath.npos) {
		thepath = thepath.substr(0, lastsepind);
		//partrace("Adding directory '%s' to the whitelist", thepath.c_str());
		ParGM()->AddDirectoryToBundleWhitelist(thepath.c_str());
	}
}

funcdef(ParInput_GetGlyphPNGForActionOrigin) {
	ensureargc(3);

	auto str{
		SteamInput()->GetGlyphPNGForActionOrigin(
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 0)),
			parcast<ESteamInputGlyphSize>(ParGM()->YYGetInt32(argument, 1)),
			ParGM()->YYGetUint32(argument, 2)
		)
	};

	_AddFilesDirToWhitelist(str);
	ParGM()->YYCreateString(
		&Result,
		str
	);
}

funcdef(ParInput_GetGlyphSVGForActionOrigin) {
	ensureargc(2);

	auto str{
		SteamInput()->GetGlyphSVGForActionOrigin(
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 0)),
			ParGM()->YYGetUint32(argument, 2)
		)
	};

	_AddFilesDirToWhitelist(str);
	ParGM()->YYCreateString(
		&Result,
		str
	);
}

funcdef(ParInput_GetGlyphForActionOrigin_Legacy) {
	ensureargc(2);

	auto str{
		SteamInput()->GetGlyphForActionOrigin_Legacy(
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	};

	_AddFilesDirToWhitelist(str);
	ParGM()->YYCreateString(
		&Result,
		str
	);
}

funcdef(ParInput_GetStringForActionOrigin) {
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForActionOrigin(
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetStringForAnalogActionName) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForAnalogActionName(
			ParGM()->YYGetInt64(argument, 0)
		)
	);
}

funcdef(ParInput_StopAnalogActionMomentum) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->StopAnalogActionMomentum(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_GetMotionData) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	auto mdata{
		SteamInput()->GetMotionData(
			ParGM()->YYGetInt64(argument, 0)
		)
	};

	ParGM()->StructCreate(&Result);
	ParGM()->StructAddDouble(&Result, "rotQuatX", mdata.rotQuatX);
	ParGM()->StructAddDouble(&Result, "rotQuatY", mdata.rotQuatY);
	ParGM()->StructAddDouble(&Result, "rotQuatZ", mdata.rotQuatZ);
	ParGM()->StructAddDouble(&Result, "rotQuatW", mdata.rotQuatW);

	ParGM()->StructAddDouble(&Result, "posAccelX", mdata.posAccelX);
	ParGM()->StructAddDouble(&Result, "posAccelY", mdata.posAccelY);
	ParGM()->StructAddDouble(&Result, "posAccelZ", mdata.posAccelZ);

	ParGM()->StructAddDouble(&Result, "rotVelX", mdata.rotVelX);
	ParGM()->StructAddDouble(&Result, "rotVelY", mdata.rotVelY);
	ParGM()->StructAddDouble(&Result, "rotVelZ", mdata.rotVelZ);
}

funcdef(ParInput_TriggerVibration) {
	ensureargc(3);
	ensurekind(0, eRVK_INT64);

	SteamInput()->TriggerVibration(
		ParGM()->YYGetInt64(argument, 0),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2))
	);
}

funcdef(ParInput_TriggerVibrationExtended) {
	ensureargc(5);
	ensurekind(0, eRVK_INT64);

	SteamInput()->TriggerVibrationExtended(
		ParGM()->YYGetInt64(argument, 0),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 3)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 4))
	);
}

funcdef(ParInput_TriggerSimpleHapticEvent) {
	ensureargc(6);
	ensurekind(0, eRVK_INT64);

	SteamInput()->TriggerSimpleHapticEvent(
		ParGM()->YYGetInt64(argument, 0),
		parcast<EControllerHapticLocation>(ParGM()->YYGetInt32(argument, 1)),
		parcast<uint8>(ParGM()->YYGetInt32(argument, 2)),
		parcast<char>(ParGM()->YYGetInt32(argument, 3)),
		parcast<uint8>(ParGM()->YYGetInt32(argument, 4)),
		parcast<char>(ParGM()->YYGetInt32(argument, 5))
	);
}

funcdef(ParInput_SetLEDColor) {
	ensureargc(5);
	ensurekind(0, eRVK_INT64);

	SteamInput()->SetLEDColor(
		ParGM()->YYGetInt64(argument, 0),
		parcast<uint8>(ParGM()->YYGetInt32(argument, 1)),
		parcast<uint8>(ParGM()->YYGetInt32(argument, 2)),
		parcast<uint8>(ParGM()->YYGetInt32(argument, 3)),
		ParGM()->YYGetUint32(argument, 4)
	);
}

funcdef(ParInput_Legacy_TriggerHapticPulse) {
	ensureargc(3);
	ensurekind(0, eRVK_INT64);

	SteamInput()->Legacy_TriggerHapticPulse(
		ParGM()->YYGetInt64(argument, 0),
		parcast<ESteamControllerPad>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2))
	);
}

funcdef(ParInput_Legacy_TriggerRepeatedHapticPulse) {
	ensureargc(6);
	ensurekind(0, eRVK_INT64);

	SteamInput()->Legacy_TriggerRepeatedHapticPulse(
		ParGM()->YYGetInt64(argument, 0),
		parcast<ESteamControllerPad>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 3)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 4)),
		ParGM()->YYGetUint32(argument, 5)
	);
}

funcdef(ParInput_ShowBindingPanel) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->ShowBindingPanel(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetInputTypeForHandle) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetInputTypeForHandle(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetControllerForGamepadIndex) {
	ensureargc(1);

	Result = RValue{
		SteamInput()->GetControllerForGamepadIndex(
			ParGM()->YYGetInt32(argument, 0)
		)
	};
}

funcdef(ParInput_GetGamepadIndexForController) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetGamepadIndexForController(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetStringForXboxOrigin) {
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForXboxOrigin(
			parcast<EXboxOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetGlyphForXboxOrigin) {
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetGlyphForXboxOrigin(
			parcast<EXboxOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetActionOriginFromXboxOrigin) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetActionOriginFromXboxOrigin(
			ParGM()->YYGetInt64(argument, 0),
			parcast<EXboxOrigin>(ParGM()->YYGetInt32(argument, 1))
		)
	};
}

funcdef(ParInput_TranslateActionOrigin) {
	ensureargc(2);

	Result = RValue{
		SteamInput()->TranslateActionOrigin(
			parcast<ESteamInputType>(ParGM()->YYGetInt32(argument, 0)),
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 1))
		)
	};
}

funcdef(ParInput_GetDeviceBindingRevision) {
	ensureargc(3);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_OBJECT);
	ensurekind(2, eRVK_OBJECT);

	int major{ }, minor{ };

	auto res{
		SteamInput()->GetDeviceBindingRevision(
			ParGM()->YYGetInt64(argument, 0),
			&major,
			&minor
		)
	};

	ParGM()->StructAddInt(&argument[1], "refval", major);
	ParGM()->StructAddInt(&argument[2], "refval", minor);

	Result = RValue{ res };
}

funcdef(ParInput_GetRemotePlaySessionID) {
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetRemotePlaySessionID(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetSessionInputConfigurationSettings) {
	Result = RValue{
		parcast<int>(
			SteamInput()->GetSessionInputConfigurationSettings()
		)
	};
}

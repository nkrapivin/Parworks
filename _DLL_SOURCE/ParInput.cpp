#include "Par.h"
#include "ParGM.h"
#include <array>
#include <string>

funcdef(ParInput_Init) {
	ensureiptr(SteamInput());
	ensureargc(1);
	
	Result = RValue{
		SteamInput()->Init(
			ParGM()->YYGetBool(argument, 0)
		)
	};
}

funcdef(ParInput_Shutdown) {
	ensureiptr(SteamInput());

	Result = RValue{
		SteamInput()->Shutdown()
	};
}

funcdef(ParInput_SetInputActionManifestFilePath) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->SetInputActionManifestFilePath(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_RunFrame) {
	ensureiptr(SteamInput());

	if (argument_count < 1 || argument[0].typeOf() == eRVK_UNDEFINED) {
		SteamInput()->RunFrame();
	}
	else {
		SteamInput()->RunFrame(
			ParGM()->YYGetBool(argument, 0)
		);
	}
}

funcdef(ParInput_BWaitForData) {
	ensureiptr(SteamInput());
	ensureargc(2);

	Result = RValue{
		SteamInput()->BWaitForData(
			ParGM()->YYGetBool(argument, 0),
			ParGM()->YYGetUint32(argument, 1)
		)
	};
}

funcdef(ParInput_BNewDataAvailable) {
	ensureiptr(SteamInput());

	Result = RValue{
		SteamInput()->BNewDataAvailable()
	};
}

funcdef(ParInput_GetConnectedControllers) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_ARRAY);

	std::array<InputHandle_t, STEAM_INPUT_MAX_COUNT> c{};
	
	int len{
		SteamInput()->GetConnectedControllers(c.data())
	};

	CDisableCoW noCoW{ argument[0].arr };
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
	ensureiptr(SteamInput());

	SteamInput()->EnableDeviceCallbacks();
}

static int _EnableActionEventCallbacksFuncScriptIndex{ -1 };
static void _EnableActionEventCallbacksFunc(SteamInputActionEvent_t *pParam) {
	if (_EnableActionEventCallbacksFuncScriptIndex < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ _EnableActionEventCallbacksFuncScriptIndex }, RValue{ } };

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
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

funcdef(ParInput_EnableActionEventCallbacks) {
	ensureiptr(SteamInput());
	ensureargc(1);

	_EnableActionEventCallbacksFuncScriptIndex = ParGM()->YYGetInt32(argument, 0);

	SteamInput()->EnableActionEventCallbacks(
		(_EnableActionEventCallbacksFuncScriptIndex < 0)
		? nullptr
		: &_EnableActionEventCallbacksFunc
	);
}

funcdef(ParInput_GetActionSetHandle) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetActionSetHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_ActivateActionSet) {
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);
	
	SteamInput()->ActivateActionSet(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_GetCurrentActionSet) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetCurrentActionSet(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_ActivateActionSetLayer) {
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->ActivateActionSetLayer(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_DeactivateActionSetLayer) {
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->DeactivateActionSetLayer(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_DeactivateAllActionSetLayers) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	SteamInput()->DeactivateAllActionSetLayers(
		ParGM()->YYGetInt64(argument, 0)
	);
}

funcdef(ParInput_GetActiveActionSetLayers) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_ARRAY);

	std::array<InputActionSetHandle_t, STEAM_INPUT_MAX_ACTIVE_LAYERS> l{};

	int len{
		SteamInput()->GetActiveActionSetLayers(
			ParGM()->YYGetInt64(argument, 0),
			l.data()
		)
	};

	CDisableCoW noCoW{ argument[0].arr };
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
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetDigitalActionHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_GetDigitalActionData) {
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	InputDigitalActionData_t acdata{
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
	ensureiptr(SteamInput());
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

	CDisableCoW noCoW{ argument[3].arr };
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
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_STRING);

	Result = RValue{
		SteamInput()->GetAnalogActionHandle(
			ParGM()->YYGetString(argument, 0)
		)
	};
}

funcdef(ParInput_GetAnalogActionData) {
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	InputAnalogActionData_t acdata{
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
	ensureiptr(SteamInput());
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

	CDisableCoW noCoW{ argument[3].arr };
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
		//partrace("Adding file '%s' to the whitelist", str);

		// and now actually add both the directory and the filename...
		ParGM()->AddDirectoryToBundleWhitelist(thepath.c_str());
		ParGM()->AddFileToBundleWhitelist(str);
		// obligatory #JustGameMakerThings
		ParGM()->AddDirectoryToSaveWhitelist(thepath.c_str());
		ParGM()->AddFileToSaveWhitelist(str);
	}
}

funcdef(ParInput_GetGlyphPNGForActionOrigin) {
	ensureiptr(SteamInput());
	ensureargc(3);

	const char* str{
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
	ensureiptr(SteamInput());
	ensureargc(2);

	const char* str{
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
	ensureiptr(SteamInput());
	ensureargc(2);

	const char* str{
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
	ensureiptr(SteamInput());
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForActionOrigin(
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetStringForAnalogActionName) {
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_INT64);

	SteamInput()->StopAnalogActionMomentum(
		ParGM()->YYGetInt64(argument, 0),
		ParGM()->YYGetInt64(argument, 1)
	);
}

funcdef(ParInput_GetMotionData) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	InputMotionData_t mdata{
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
	ensureiptr(SteamInput());
	ensureargc(3);
	ensurekind(0, eRVK_INT64);

	SteamInput()->TriggerVibration(
		ParGM()->YYGetInt64(argument, 0),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2))
	);
}

funcdef(ParInput_TriggerVibrationExtended) {
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
	ensureargc(3);
	ensurekind(0, eRVK_INT64);

	SteamInput()->Legacy_TriggerHapticPulse(
		ParGM()->YYGetInt64(argument, 0),
		parcast<ESteamControllerPad>(ParGM()->YYGetInt32(argument, 1)),
		parcast<unsigned short>(ParGM()->YYGetInt32(argument, 2))
	);
}

funcdef(ParInput_Legacy_TriggerRepeatedHapticPulse) {
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->ShowBindingPanel(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetInputTypeForHandle) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetInputTypeForHandle(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetControllerForGamepadIndex) {
	ensureiptr(SteamInput());
	ensureargc(1);

	Result = RValue{
		SteamInput()->GetControllerForGamepadIndex(
			ParGM()->YYGetInt32(argument, 0)
		)
	};
}

funcdef(ParInput_GetGamepadIndexForController) {
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetGamepadIndexForController(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetStringForXboxOrigin) {
	ensureiptr(SteamInput());
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetStringForXboxOrigin(
			parcast<EXboxOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetGlyphForXboxOrigin) {
	ensureiptr(SteamInput());
	ensureargc(1);

	ParGM()->YYCreateString(
		&Result,
		SteamInput()->GetGlyphForXboxOrigin(
			parcast<EXboxOrigin>(ParGM()->YYGetInt32(argument, 0))
		)
	);
}

funcdef(ParInput_GetActionOriginFromXboxOrigin) {
	ensureiptr(SteamInput());
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
	ensureiptr(SteamInput());
	ensureargc(2);

	Result = RValue{
		SteamInput()->TranslateActionOrigin(
			parcast<ESteamInputType>(ParGM()->YYGetInt32(argument, 0)),
			parcast<EInputActionOrigin>(ParGM()->YYGetInt32(argument, 1))
		)
	};
}

funcdef(ParInput_GetDeviceBindingRevision) {
	ensureiptr(SteamInput());
	ensureargc(3);
	ensurekind(0, eRVK_INT64);
	ensurekind(1, eRVK_OBJECT);
	ensurekind(2, eRVK_OBJECT);

	int major{ 0 }, minor{ 0 };

	bool res{
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
	ensureiptr(SteamInput());
	ensureargc(1);
	ensurekind(0, eRVK_INT64);

	Result = RValue{
		SteamInput()->GetRemotePlaySessionID(
			ParGM()->YYGetInt64(argument, 0)
		)
	};
}

funcdef(ParInput_GetSessionInputConfigurationSettings) {
	ensureiptr(SteamInput());

	Result = RValue{
		parcast<int>(
			SteamInput()->GetSessionInputConfigurationSettings()
		)
	};
}

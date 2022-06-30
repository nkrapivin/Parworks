// global callback functions:

/// @desc Par callback functions
enum EParCallbackFunction {
	k_First = 0,
	// add these here:
	k_OnSteamInputConfigurationLoaded = EParCallbackFunction.k_First,
	k_OnSteamInputDeviceConnected,
	k_OnSteamInputDeviceDisconnected,
	k_OnFloatingGamepadTextInputDismissed,
	k_OnGamepadTextInputDismissed,
	k_OnAppResumingFromSuspend,
	k_OnSteamShutdown,
	k_OnRemoteStorageLocalFileChange,
	k_OnSteamServersConnected,
	k_OnSteamServersDisconnected,
	k_OnSteamServerConnectFailure,
	k_OnSteamAPICallCompleted,
	k_OnLowBatteryPower,
	k_OnIPCountry,
	k_OnValidateAuthTicketResponse,
	k_OnGameWebCallback,
	k_OnGetAuthSessionTicketResponse,
	k_OnLicensesUpdated,
	k_OnIPCFailure,
	k_OnMicroTxnAuthorizationResponse,
	k_OnClientGameServerDeny,
	// and here it ends
	k_Max
};

/// @desc Allows you to attach to Par callback functions.
/// @param {EParCallbackFunction} eCallbackType Callback function to attach to
/// @param {Any} [callFunction] Any callable object, be it a script index or a method
/// @param {Any} [userData] Additional second argument to be provided to the function
/// @returns callback object
function Par_AttachTo(eCallbackType, callFunction = undefined, userData = undefined) {
	if (is_undefined(eCallbackType)) {
		throw "Par_AttachTo: Invalid argument eCallbackType, cannot be undefined.";
	}
	
	if (eCallbackType <  EParCallbackFunction.k_First
	||  eCallbackType >= EParCallbackFunction.k_Max) {
		throw "Par_AttachTo: Invalid argument eCallbackType, enum EParCallbackFunction out of range.";
	}
	
	var _cbs = array_length(global._Par_Callbacks[@ eCallbackType]);
	var _cbstruct = new _Par_CallbackObject(callFunction, userData);
	global._Par_Callbacks[@ eCallbackType][@ _cbs] = _cbstruct;
	return _cbstruct;
}

/// @param pParam SteamInputConfigurationLoaded_t* see Steamworks SDK documentation
function Par_OnSteamInputConfigurationLoaded(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamInputConfigurationLoaded, pParam);
}

/// @param pParam SteamInputDeviceConnected_t* see Steamworks SDK documentation
function Par_OnSteamInputDeviceConnected(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamInputDeviceConnected, pParam);
}

/// @param pParam SteamInputDeviceDisconnected_t* see Steamworks SDK documentation
function Par_OnSteamInputDeviceDisconnected(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamInputDeviceDisconnected, pParam);
}

/// @param pParam FloatingGamepadTextInputDismissed_t* see Steamworks SDK documentation
function Par_OnFloatingGamepadTextInputDismissed(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnFloatingGamepadTextInputDismissed, pParam);
}

/// @param pParam GamepadTextInputDismissed_t* see Steamworks SDK documentation
function Par_OnGamepadTextInputDismissed(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnGamepadTextInputDismissed, pParam);
}

/// @param pParam AppResumingFromSuspend_t* see Steamworks SDK documentation
function Par_OnAppResumingFromSuspend(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnAppResumingFromSuspend, pParam);
}

/// @param pParam SteamShutdown_t* see Steamworks SDK documentation
function Par_OnSteamShutdown(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamShutdown, pParam);
}

/// @param pParam RemoteStorageLocalFileChange_t* see Steamworks SDK documentation
function Par_OnRemoteStorageLocalFileChange(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnRemoteStorageLocalFileChange, pParam);
}

/// @param pParam SteamServersConnected_t* see Steamworks SDK documentation
function Par_OnSteamServersConnected(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamServersConnected, pParam);
}

/// @param pParam SteamServersDisconnected_t* see Steamworks SDK documentation
function Par_OnSteamServersDisconnected(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamServersDisconnected, pParam);
}

/// @param pParam SteamServerConnectFailure_t* see Steamworks SDK documentation
function Par_OnSteamServerConnectFailure(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamServerConnectFailure, pParam);
}

/// @param pParam SteamAPICallCompleted_t* see Steamworks SDK documentation
function Par_OnSteamAPICallCompleted(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnSteamAPICallCompleted, pParam);
}

/// @param pParam LowBatteryPower_t* see Steamworks SDK documentation
function Par_OnLowBatteryPower(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnLowBatteryPower, pParam);
}

/// @param pParam IPCountry_t* see Steamworks SDK documentation
function Par_OnIPCountry(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnIPCountry, pParam);
}

/// @param pParam ValidateAuthTicketResponse_t* see Steamworks SDK documentation
function Par_OnValidateAuthTicketResponse(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnValidateAuthTicketResponse, pParam);
}

/// @param pParam GameWebCallback_t* see Steamworks SDK documentation
function Par_OnGameWebCallback(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnGameWebCallback, pParam);
}

/// @param pParam GetAuthSessionTicketResponse_t* see Steamworks SDK documentation
function Par_OnGetAuthSessionTicketResponse(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnGetAuthSessionTicketResponse, pParam);
}

/// @param pParam LicensesUpdated_t* see Steamworks SDK documentation
function Par_OnLicensesUpdated(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnLicensesUpdated, pParam);
}

/// @param pParam IPCFailure_t* see Steamworks SDK documentation
function Par_OnIPCFailure(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnIPCFailure, pParam);
}

/// @param pParam MicroTxnAuthorizationResponse_t* see Steamworks SDK documentation
function Par_OnMicroTxnAuthorizationResponse(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnMicroTxnAuthorizationResponse, pParam);
}

/// @param pParam ClientGameServerDeny_t* see Steamworks SDK documentation
function Par_OnClientGameServerDeny(pParam) {
	return _Par_PerformCallbacks(EParCallbackFunction.k_OnClientGameServerDeny, pParam);
}

/*-- DO NOT TOUCH THE STUFF BELOW --*/






























global._Par_WarningMessageHookArray = [];
function _Par_WarningMessageHookFunction(nSeverity, pchDebugText) {
	var _i;
	
	for (_i = 0; _i < array_length(global._Par_WarningMessageHookArray); ++_i) {
		var _tuple = global._Par_WarningMessageHookArray[@ _i];
		if (!is_undefined(_tuple)) {
			var _func = _tuple[@ 0];
			var _userData = _tuple[@ 1];
			if (!is_undefined(_func)) {
				_func(nSeverity, pchDebugText, _userData);
			}
		}
	}
	
	return _i;
}

function ParUtils_SetWarningMessageHook(pFunction, userData = undefined) {
	if (is_undefined(pFunction)) {
		array_resize(global._Par_WarningMessageHookArray, 0);
		_ParUtils_SetWarningMessageHook(-1);
	}
	else {
		var _cblen = array_length(global._Par_WarningMessageHookArray);
		global._Par_WarningMessageHookArray[@ _cblen] = [
			pFunction,
			userData
		];
		_ParUtils_SetWarningMessageHook(_Par_WarningMessageHookFunction);
	}
}






global._Par_EnableActionEventCallbacksArray = []; // array of _Par_PerformCallbacks

function _Par_ThingCalledByEnableActionEventCallbacks(pParam) {
	var _i;
	
	for (_i = 0; _i < array_length(global._Par_EnableActionEventCallbacksArray); ++_i) {
		var _cb = global._Par_EnableActionEventCallbacksArray[@ _i];
		
		if (!is_undefined(_cb)) {
			_cb._PerformCallback(pParam);
		}
	}
	
	return _i;
}

/// @desc An ugly hack around Script_Execute in the runner...
function ParInput_EnableActionEventCallbacks(pCallback, userData = undefined) {
	if (is_undefined(pCallback)) {
		// this will silence action event callbacks...
		array_resize(global._Par_EnableActionEventCallbacksArray, 0);
		_ParInput_EnableActionEventCallbacks(-1);
		return undefined;
	}
	else {
		var _cb = new _Par_CallbackObject(pCallback, userData);
		var _cblen = array_length(global._Par_EnableActionEventCallbacksArray);
		global._Par_EnableActionEventCallbacksArray[@ _cblen] = _cb;
		// global scripts do work, methods do not, I want to allow methods
		_ParInput_EnableActionEventCallbacks(_Par_ThingCalledByEnableActionEventCallbacks);
		return _cb;
	}
}











function _Par_CallbackObject(argcallFunction, arguserData) constructor {
// private:

	m_callFunction = argcallFunction;
	
	m_userData = arguserData;
	
	_PerformCallback = function(pParam) {
		if (!is_undefined(m_callFunction)) {
			return m_callFunction(pParam, m_userData);
		}
		
		return undefined;
	};
	
// public:

	GetCallFunction = function() {
		return m_callFunction;
	};
	
	IsCallFunctionPresent = function() {
		return !is_undefined(m_callFunction);
	};
	
	SetCallFunction = function(newCallFunction) {
		m_callFunction = newCallFunction;
		return self;
	};
	
	GetUserData = function() {
		return m_userData;
	};
	
	IsUserDataPresent = function() {
		return !is_undefined(m_userData);
	};
	
	SetUserData = function(newUserData = undefined) {
		m_userData = newUserData;
		return self;
	};
}

global._Par_Callbacks = array_create(EParCallbackFunction.k_Max, undefined);
for (var _i = EParCallbackFunction.k_First; _i != EParCallbackFunction.k_Max; ++_i) {
	global._Par_Callbacks[@ _i] = array_create(0); // array of _Par_CallbackObject
}

function _Par_PerformCallbacks(eCallbackType, pParam) {
	var _i;
	
	for (_i = 0; _i < array_length(global._Par_Callbacks[@ eCallbackType]); ++_i) {
		var _thiscb = global._Par_Callbacks[@ eCallbackType][@ _i];
		
		if (!is_undefined(_thiscb)) {
			_thiscb._PerformCallback(pParam);
		}
	}
	
	// returns the amount of performed callbacks, can be used for profiler purposes.
	return _i;
}



function _Par_CallbackHost() constructor {
	// has nothing, this is a `self` for all Par callback functions
	m_bFlag = false; // reserved for future use
	m_iReserved = 0;
	m_i64Reserved = int64("0");
}

// must be static!
global._Par_F_ScriptExecute = method(undefined, script_execute);
global._Par_CallbackSelf = new _Par_CallbackHost(); // will act as `self` for all callbacks
_Par_ScriptCallSetup(global._Par_F_ScriptExecute, global._Par_CallbackSelf);

function ParCallbacks() {
	return "<ParCallbacks>: Do not call this function!";
}





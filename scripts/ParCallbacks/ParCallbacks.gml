// global callback functions:

/// @desc Par callback functions
enum EParCallbackFunction {
	k_First = 0,
	// add these here:
	k_OnSteamInputConfigurationLoaded = 0,
	k_OnSteamInputDeviceConnected,
	k_OnSteamInputDeviceDisconnected,
	k_OnFloatingGamepadTextInputDismissed,
	k_OnGamepadTextInputDismissed,
	k_OnAppResumingFromSuspend,
	k_OnSteamShutdown,
	// and here it ends
	k_Max
};

/// @desc Allows you to attach to Par callback functions.
/// @param {EParCallbackFunction} eCallbackType Callback function to attach to
/// @param {Any} callFunction Any callable object, be it a script index or a method
/// @param {Any} [userData] Additional second argument to be provided to the function
function Par_AttachTo(eCallbackType, callFunction, userData = undefined) {
	if (is_undefined(eCallbackType)) {
		throw "Par_AttachTo: Invalid argument eCallbackType, cannot be undefined.";
	}
	
	if (eCallbackType <  EParCallbackFunction.k_First
	||  eCallbackType >= EParCallbackFunction.k_Max) {
		throw "Par_AttachTo: Invalid argument eCallbackType, enum EParCallbackFunction out of range.";
	}
	
	if (is_undefined(callFunction)) {
		throw "Par_AttachTo: Invalid argument callFunction, cannot be undefined.";
	}
	
	var _cbs = array_length(global._Par_Callbacks[@ eCallbackType]);
	global._Par_Callbacks[@ eCallbackType][@ _cbs] = new _Par_CallbackObject(callFunction, userData);
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

/*-- DO NOT TOUCH THE STUFF BELOW --*/




































global._Par_EnableActionEventCallbacksThing = undefined;

function _Par_ThingCalledByEnableActionEventCallbacks(pParam) {
	if (!is_undefined(global._Par_EnableActionEventCallbacksThing)) {
		global._Par_EnableActionEventCallbacksThing(pParam);
	}
}

/// @desc An ugly hack around Script_Execute in the runner...
function ParInput_EnableActionEventCallbacks(pCallback) {
	if (is_undefined(pCallback)) {
		// this will silence action event callbacks...
		_ParInput_EnableActionEventCallbacks(-1);
	}
	else {
		global._Par_EnableActionEventCallbacksThing = pCallback;
		// global scripts do work, methods do not, I want to allow methods
		_ParInput_EnableActionEventCallbacks(_Par_ThingCalledByEnableActionEventCallbacks);
	}
}











function _Par_CallbackObject(argcallFunction, arguserData) constructor {
	m_callFunction = argcallFunction;
	m_userData = arguserData;
	
	PerformCallback = function(pParam) {
		return m_callFunction(pParam, m_userData);
	};
}

global._Par_Callbacks = array_create(EParCallbackFunction.k_Max, undefined);
for (var _i = EParCallbackFunction.k_First; _i != EParCallbackFunction.k_Max; ++_i) {
	global._Par_Callbacks[@ _i] = array_create(0); // array of _Par_CallbackObject
}

function _Par_PerformCallbacks(eCallbackType, pParam) {
	var _i;
	var _cbsarr = global._Par_Callbacks[@ eCallbackType];
	var _cbslen = array_length(_cbsarr);
	
	for (_i = 0; _i < _cbslen; ++_i) {
		var _thiscb = _cbsarr[@ _i];
		
		if (!is_undefined(_thiscb)) {
			_thiscb.PerformCallback(pParam);
		}
	}
	
	// returns the amount of performed callbacks, can be used for profiler purposes.
	return _i;
}







function _Par_CallbackHost() constructor {
	// has nothing, this is a `self` for all Par callback functions
	m_bFlag = false; // unused
}

// must be static!
global._Par_F_ScriptExecute = method(undefined, script_execute);
global._Par_CallbackSelf = new _Par_CallbackHost(); // will act as `self` for all callbacks
Par_ScriptCallSetup(global._Par_F_ScriptExecute, global._Par_CallbackSelf);

function ParCallbacks() {
	return "<ParCallbacks>: Do not call this function!";
}





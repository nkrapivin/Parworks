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
	k_OnRemoteStorageLocalFileChange,
	k_OnSteamServersConnected,
	k_OnSteamServersDisconnected,
	k_OnSteamServerConnectFailure,
	k_OnSteamAPICallCompleted,
	k_OnLowBatteryPower,
	k_OnIPCountry,
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

/// @desc Allows to attach a GML method to a call result
/// @param {Int64} hSteamAPICall SteamAPICall_t handle which cannot be null
/// @param {Any} [callFunction] Any callable object, be it a script index or a method
/// @param {Any} [userData] Additional second argument to be provided to the function
/// @returns callback object
function Par_AttachToCallResult(hSteamAPICall, callFunction = undefined, userData = undefined) {
	if (is_undefined(global._Par_CallResultsMap)) {
		Par_AttachTo(
			EParCallbackFunction.k_OnSteamAPICallCompleted,
			_Par_CallResult_OnCompleted,
			undefined
		);
		
		global._Par_CallResultsMap = ds_map_create();
	}
	
	// initially a handle can't be an int64
	// later you can call the .Cancel() method if you really want to cancel a CallResult
	if (!is_int64(hSteamAPICall)) {
		throw "\nAn API call handle MUST be an Int64. But got " + typeof(hSteamAPICall);
	}
	
	if (hSteamAPICall == Par_NullHandle) {
		throw "\nCallResult handle is Null.";
	}
	
	// yeah no not gonna work, one callresult handle = one handler
	if (ds_map_exists(global._Par_CallResultsMap, hSteamAPICall)) {
		throw "\nA callable is already attached to this API call handle.";
	}
	
	var _cbobj = new _Par_CallResultObject(callFunction, userData, hSteamAPICall);
	
	ds_map_add(
		global._Par_CallResultsMap,
		hSteamAPICall,
		_cbobj
	);
	
	return _cbobj;
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


/*-- DO NOT TOUCH THE STUFF BELOW --*/


















global._Par_CallResultsMap = undefined;

function _Par_CallResult_OnCompleted(pParam) {
	if (is_undefined(global._Par_CallResultsMap) || is_undefined(pParam)) {
		// the fuck?
		return undefined;
	}
	
	var _m_hAsyncCall = pParam.m_hAsyncCall;
	var _m_iCallback = pParam.m_iCallback;
	var _m_cubParam = pParam.m_cubParam;
	
	var _cbobj = undefined;
	if (ds_map_exists(global._Par_CallResultsMap, _m_hAsyncCall)) {
		_cbobj = ds_map_find_value(global._Par_CallResultsMap, _m_hAsyncCall);
		ds_map_delete(global._Par_CallResultsMap, _m_hAsyncCall);
	}
	
	var _buff = buffer_create(_m_cubParam, buffer_fixed, 1);
	buffer_seek(_buff, buffer_seek_start, 0);
	buffer_fill(_buff, 0, buffer_u8, 0, _m_cubParam);
	buffer_seek(_buff, buffer_seek_start, 0);
	// try to get the actual call result:
	
	var _ok = false;
	var _failedRef = { }; // .refval will be set
	var _failed = false; // bIOFailure
	var _pCallback = undefined;
	var _failReason = ESteamAPICallFailure.k_None;
	
	_ok = ParUtils_GetAPICallResult(
		_m_hAsyncCall,
		buffer_get_address(_buff),
		_m_cubParam,
		_m_iCallback,
		_failedRef
	);
	
	_failReason = ParUtils_GetAPICallFailureReason(
		_m_hAsyncCall
	);
	
	if (_ok) {
		_failed = _failedRef.refval;
	
		switch (_m_iCallback) {
			case 154: { // EncryptedAppTicketResponse_t*
				_pCallback = ParCallResult_OnEncryptedAppTicketResponse(buffer_get_address(_buff));
				break;
			}
			
			case 165: { // StoreAuthURLResponse_t*
				_pCallback = ParCallResult_OnStoreAuthURLResponse(buffer_get_address(_buff));
				break;
			}
			
			case 166: { // MarketEligibilityResponse_t*
				_pCallback = ParCallResult_OnMarketEligibilityResponse(buffer_get_address(_buff));
				break;
			}
			
			case 167: { // DurationControl_t*
				_pCallback = ParCallResult_OnDurationControl(buffer_get_address(_buff));
				break;
			}
			
			default: {
				show_error("Unsupported API CallResult :( " + string(_m_iCallback), false);
				break;
			}
		}
	}
	else {
		show_debug_message("[Par|_Par_CallResult_OnCompleted;uh oh] CallResult obtain failed, reason = " + string(_failReason));
	}
	
	if (buffer_exists(_buff)) {
		buffer_delete(_buff); // make sure the callback didn't free the buffer somehow already
		_buff = -1;
	}
	
	if (_ok && !is_undefined(_cbobj)) {
		_cbobj._PerformCallback(_pCallback, _failed);
	}
}









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


function _Par_CallResultObject(argcallFunction, arguserData, argHandle) : _Par_CallbackObject(argcallFunction, arguserData) constructor {
// private:

	// inherited from _Par_CallbackObject

	m_callResultHandle = argHandle; // Int64, SteamAPICall_t
	
	_PerformCallback = function(pCallback, bIOFailure) {
		if (IsActive() && !is_undefined(m_callFunction)) {
			return m_callFunction(pCallback, bIOFailure, m_userData);
		}
		
		return undefined;
	};
	
// public:
	
	// inherited from _Par_CallbackObject
	
	IsActive = function() {
		return (m_callResultHandle != Par_NullHandle);
	};
	
	Cancel = function() {
		if (IsActive()) {
			if (ds_map_exists(global._Par_CallResultsMap, m_callResultHandle)) {
				ds_map_delete(global._Par_CallResultsMap, m_callResultHandle);
			}
			
			m_callResultHandle = Par_NullHandle;
		}
		
		return self;
	};
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





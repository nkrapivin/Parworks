// global callback functions:

// you are allowed to modify the code inside the functions
// you are NOT allowed to rename the functions or the argument names
// you are allowed to call other functions inside these ones
// they are all called with `global` as `self` and `other`, so please disregard `self` here, call into
// an another function right away!

/// @param pParam SteamInputConfigurationLoaded_t* see Steamworks SDK documentation
function Par_OnSteamInputConfigurationLoaded(pParam) {
	show_debug_message("Par_OnSteamInputConfigurationLoaded: " + json_stringify(pParam));
}

/// @param pParam SteamInputDeviceConnected_t* see Steamworks SDK documentation
function Par_OnSteamInputDeviceConnected(pParam) {
	show_debug_message("Par_OnSteamInputDeviceConnected: " + json_stringify(pParam));
}

/// @param pParam SteamInputDeviceDisconnected_t* see Steamworks SDK documentation
function Par_OnSteamInputDeviceDisconnected(pParam) {
	show_debug_message("Par_OnSteamInputDeviceDisconnected: " + json_stringify(pParam));
}

/// @param pParam FloatingGamepadTextInputDismissed_t* see Steamworks SDK documentation
function Par_OnFloatingGamepadTextInputDismissed(pParam) {
	show_debug_message("Par_OnFloatingGamepadTextInputDismissed: " + json_stringify(pParam));
}

/*-- DO NOT TOUCH THE STUFF BELOW --*/





























































function _Par_CallbackHost() constructor {
	// has nothing, this is a `self` for all Par callback functions
}

// must be static!
static _Par_F_ScriptExecute = method(undefined, script_execute);
static _Par_CallbackSelf = new _Par_CallbackHost(); // will act as `self` for all callbacks
Par_ScriptCallSetup(_Par_F_ScriptExecute, _Par_CallbackSelf);

function ParCallbacks() {
	return "<ParCallbacks>: Do not call this function!";
}


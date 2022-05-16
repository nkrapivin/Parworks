
// With this function you can create a new leaderboard for your game.
// This call just assures we have a leaderboard to work with for later calls.

randomize();
steam_set_warning_message_hook();

#macro SteamLeaderboard "YYLeaderboard_10/29/21--"

zero = int64(0);

Par_AttachTo(
	EParCallbackFunction.k_OnSteamInputConfigurationLoaded,
	function(pParam, userData = undefined) {
		with (Obj_Steam_GeneralInfo) {
			txt += string(userData) + " - " + string(pParam.m_ulDeviceHandle) + "\n";
		}
	},
	"i love wearing cat ears"
);

Par_AttachTo(
	EParCallbackFunction.k_OnFloatingGamepadTextInputDismissed,
	function(pParam, userData = undefined) {
		with (Obj_Steam_GeneralInfo) {
			txt += "Floating Keyboard Dismissed! get_timer()=" + string(get_timer()) + "\n";
		}
	}
	//, [] // optional userdata, will be the `userData` argument if provided
	// allows for stuff like lambdas and variable captures.
);

Par_AttachTo(
	EParCallbackFunction.k_OnGamepadTextInputDismissed,
	function(pParam, userData = undefined) {
		var _textRef = {}; // must be an empty struct
		var _len = ParUtils_GetEnteredGamepadTextLength();
		ParUtils_GetEnteredGamepadTextInput(_textRef, _len);
		var _text = _textRef.refval;
	
		with (Obj_Steam_GeneralInfo) {
			txt += "Tenfoot Keyboard Dismissed! t=" + string(get_timer()) + ",s='" + _text + "'." + "\n";
		}
	}
);


// initialize Steam Input:
var _ok = ParInput_Init(false);
show_debug_message("ParInput_Init(): " + string(_ok));
if (!_ok)
	throw "\nUnable to initialize Parworks or ParInput";
	
ParInput_EnableDeviceCallbacks();

// theyre all int64s!!
mycon = zero;
mycontype = zero;
myconfire_lasers = zero;
myconanalog = zero;
flag = false;

justthisonce = false;
glyphspr = -1;

onActionEventCallback = function(pParam) {
	show_debug_message("Action state change:");
	show_debug_message(json_stringify(pParam));
	
	if (pParam.controllerHandle == mycon
	&&  pParam.eEventType == ESteamInputActionEventType.k_DigitalAction) {
		
		var _dighandle = pParam.digitalAction.actionHandle;
		
		if (_dighandle == myconfire_lasers) {
			var _digaction = pParam.digitalAction.digitalActionData;
			if (_digaction.bActive && _digaction.bState) {
				// clear kbd string before invoking a keyboard.
				keyboard_string = "";
				
				if (flag)
				ParUtils_ShowGamepadTextInput(
					EGamepadTextInputMode.k_Normal,
					EGamepadTextInputLineMode.k_SingleLine,
					"A description:",
					64,
					"existing text"
				);
				else
				ParUtils_ShowFloatingGamepadTextInput(
					EFloatingGamepadTextInputMode.k_ModeSingleLine,
					0,
					window_get_height()/2,
					window_get_width(),
					window_get_height()/2
				);
			}
		}
	}
};


room_goto(Room_Steam_Main);


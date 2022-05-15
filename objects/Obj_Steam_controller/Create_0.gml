
// With this function you can create a new leaderboard for your game.
// This call just assures we have a leaderboard to work with for later calls.

randomize();
steam_set_warning_message_hook();

#macro SteamLeaderboard "YYLeaderboard_10/29/21--"

zero = int64(0);



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

// must be a global function script, not a method! so we have the index not a method struct.
function __Obj_Steam_controller_onActionEventCallback(pParam) {
	// this function is called in a different `self`, need to do a with() into the real callback.
	with (Obj_Steam_controller) {
		onActionEventCallback(pParam);
	}
}

//  !!!!!!!!!!!! this is what you pass into the ParInput_EnableActionEventCallbacks function !!!!!!!!!
onActionEventIndex = __Obj_Steam_controller_onActionEventCallback;


room_goto(Room_Steam_Main);


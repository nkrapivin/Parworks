
// With this function you can create a new leaderboard for your game.
// This call just assures we have a leaderboard to work with for later calls.

randomize();

#macro SteamLeaderboard "YYLeaderboard_10/29/21--"

// initialize Steam Input:
var _ok = ParInput_Init(false);
show_debug_message("ParInput_Init(): " + string(_ok));

zero = int64(0);

// theyre all int64s!!
mycon = zero;
mycontype = zero;
myconset = zero;
myconanalog = zero;

justthisonce = false;
glyphspr = -1;

function __onActionEventCallback(pParam) {
	show_debug_message("Action state change:");
	show_debug_message(json_stringify(pParam));
}

//  !!!!!!!!!!!! this is what you pass into the Par function !!!!!!!!!
onActionEventIndex = is_numeric(__onActionEventCallback)
	? __onActionEventCallback
	: method_get_index(__onActionEventCallback);


room_goto(Room_Steam_Main);


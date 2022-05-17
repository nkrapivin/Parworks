
// This needs to be called every frame so that the extension
// gets updated you should place this call in a controller object
// that is persistent through the entire duration of you game.
steam_update();

if (keyboard_check_pressed(vk_tab)) flag = !flag;

var _controllers = [];
var _num = ParInput_GetConnectedControllers(_controllers);
if (_num > 0) {
	mycon = _controllers[@ 0]; // grab the first con.
	mycontype = ParInput_GetInputTypeForHandle(mycon);
	myconfire_lasers = ParInput_GetDigitalActionHandle("fire_lasers");
	myconanalog = ParInput_GetAnalogActionHandle("analog_controls");
	
	if (!justthisonce) {
		justthisonce = true;
		ParInput_EnableActionEventCallbacks(onActionEventCallback);
		ParInput_EnableActionEventCallbacks(function(pParam, test) {
			show_debug_message("and an another callback: " + test);
		}, "hello userdata test");
		
		var _path = ParInput_GetGlyphPNGForActionOrigin(
			EInputActionOrigin.k_PS4_Circle,
			ESteamInputGlyphSize.k_Medium,
			0
		);
		// ^^ if the _path exists, Parworks will add this file into the GameMaker whitelist
		// no need to do the sandbox funnies
		if (file_exists(_path)) {
			// removeback and smooth MUST BE FALSE
			// origin can be set to the middle if you want
			sprite_index = sprite_add(_path, 1, false, false, 0, 0);
			x = 256;
			y = 256;
		}
	}
}

// -- invoke steam input binding -- //
if (keyboard_check_pressed(ord("B")) && mycon != zero) {
	ParInput_ShowBindingPanel(mycon);
}

if (keyboard_check_pressed(ord("P")) && mycon != zero) {
	show_debug_message("CONTROLLER STEAM TYPE == " + string(mycontype));
	ParUtils_DismissFloatingGamepadTextInput();
}



//ParInput_GetDigitalActionData()







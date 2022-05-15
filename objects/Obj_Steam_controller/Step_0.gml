
// This needs to be called every frame so that the extension
// gets updated you should place this call in a controller object
// that is persistent through the entire duration of you game.
steam_update();

var _controllers = [];
var _num = ParInput_GetConnectedControllers(_controllers);
if (_num > 0) {
	mycon = _controllers[@ 0]; // grab the first con.
	mycontype = ParInput_GetInputTypeForHandle(mycon);
	myconset = ParInput_GetDigitalActionHandle("fire_lasers");
	myconanalog = ParInput_GetAnalogActionHandle("analog_controls");
	
	if (!justthisonce) {
		justthisonce = true;
		ParInput_EnableActionEventCallbacks(onActionEventIndex);
		
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

if (mycon != zero) {
	var _data = ParInput_GetDigitalActionData(mycon, myconset);
	if (_data.bActive && _data.bState) {
		//window_set_caption("hello and goodnight, do you feel alrite? " + string(get_timer()));
	}
	
	var _adata = ParInput_GetAnalogActionData(mycon, myconanalog);
	if (_adata.bActive) {
		window_set_caption("x="+string(_adata.x) + ",y=" + string(_adata.y));
	}
}

// -- invoke steam input binding -- //
if (keyboard_check_pressed(ord("B")) && mycon != zero) {
	ParInput_ShowBindingPanel(mycon);
}

if (keyboard_check_pressed(ord("P")) && mycon != zero) {
	show_debug_message("CONTROLLER STEAM TYPE == " + string(mycontype));
	var _Ok = ParUtils_ShowFloatingGamepadTextInput(
		EFloatingGamepadTextInputMode.k_ModeSingleLine,
		0,
		0,
		window_get_width(),
		window_get_height()/2
	);
	show_debug_message("ParUtils_ShowFloatingGamepadTextInput: " + string(_Ok));
}



//ParInput_GetDigitalActionData()







/// @description poll, man...

update();

/*
//uncomment this to test out regular gm pad detection...
var __i = 0, _s = "";
repeat (32) {
	//if (gamepad_button_check_released(__i, gp_face3)) {
		if (gamepad_get_description(__i) != "")
			_s += gamepad_get_description(__i) + " ";
	//}
	
	++__i;
}

if (_s != "") window_set_caption(_s);
*/


/// @description funny

draw_set_font(Font_YoYo_20);
draw_set_valign(fa_top);
draw_set_halign(fa_left);
draw_set_alpha(1);
draw_set_color(c_white);

_t = 0;
_dc = deviceCount();

if (_dc <= 0) {
	draw_text(50, 100 + ((_t++) * 30), "No controllers detected, is Steam Input running?");
}
else {
	
	draw_text(50, 100 + ((_t++) * 30), "Input info (Press I to open Steam Input Configurator, arrows to scroll through devices):");
	draw_text(50, 100 + ((_t++) * 30), "Press 'M' to activate Menu action set, 'G' to inGame action set. 'V' vibration");
	draw_text(50, 100 + ((_t++) * 30), "Device: " + string(_d) + " out of " + string(_dc) + ", type = " + string(getInputType(_d)));
	draw_text(50, 100 + ((_t++) * 30), "FYI all glyphs are fetched from Steamworks directly");
	
	var _daxis = keyboard_check_pressed(vk_right) - keyboard_check_pressed(vk_left);
	if (_daxis != 0) {
		_d += _daxis;
		if (_d < 0) _d = _dc - 1;
		else if (_d >= _dc) _d = 0;
		exit;
	}
	
	if (keyboard_check_pressed(ord("I"))) {
		showBindingPanel(_d);
	}
	
	if (keyboard_check_pressed(ord("M"))) {
		activateActionSet(_d, "MenuControls");
		exit;
	}
	
	if (keyboard_check_pressed(ord("G"))) {
		activateActionSet(_d, "InGameControls");
		exit;
	}
	
	if (keyboard_check_pressed(ord("V"))) {
		vflag = !vflag;
		vibraHelper(_d, vflag * 100000, vflag * 100000);
	}
	
	var _a = getActionSet(_d);
	
	drawAction = function(deviceIndex, actionSetName, actionName, isDigital) {
		var _uidata = getActionUIData(deviceIndex, actionSetName, actionName);
		var _uidatab = _uidata.buttons;
		var _data = getActionData(deviceIndex, actionSetName, actionName);
		
		var _x = 50;
		var _y = 100 + ((_t++) * 30);
		
		var _btnpref = "(" + _uidata.locname + ":";
		for (var _i = 0; _i < array_length(_uidatab); ++_i) {
			var _btnbtn = _uidata.buttons[@ _i];
			_btnpref += _btnbtn.name;
			if (_i < array_length(_uidatab) - 1) _btnpref += ",";
			
			draw_sprite(_btnbtn.spr, 0, _x, _y);
			_x += sprite_get_width(_btnbtn.spr) + 1;
		}
		_btnpref += ")";
		
		draw_text(_x, _y, actionName + _btnpref + "=" + (isDigital? formatDigital(_data): formatAnalog(_data)));
	};
	
	if (is_undefined(_a)) {
		draw_text(50, 100 + ((_t++) * 30), "Assigning an action set...");
	}
	else if (_a == "InGameControls") {
		drawAction(_d, _a, "Move", false);
		drawAction(_d, _a, "Camera", false);
		drawAction(_d, _a, "Throttle", false);
		drawAction(_d, _a, "fire", true);
		drawAction(_d, _a, "Jump", true);
		drawAction(_d, _a, "pause_menu", true);
	}
	else if (_a == "MenuControls") {
		drawAction(_d, _a, "menu_up", true);
		drawAction(_d, _a, "menu_down", true);
		drawAction(_d, _a, "menu_left", true);
		drawAction(_d, _a, "menu_right", true);
		drawAction(_d, _a, "menu_select", true);
		drawAction(_d, _a, "menu_cancel", true);
		drawAction(_d, _a, "pause_menu", true);
	}
	else {
		draw_text(50, 100 + ((_t++) * 30), "Unknown action set...??? " + _a);
	}
}




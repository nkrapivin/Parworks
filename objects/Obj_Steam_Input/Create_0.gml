/// @description oh god

/*--

	This is a very very horrible implementation of GML Steam Input.
	
	Please do not take it seriously.

--*/

internalInit = function() {
	zero = int64("0"); // a null handle, yes, must be an int64
	allcons = STEAM_INPUT_HANDLE_ALL_CONTROLLERS;
	handles = array_create(STEAM_INPUT_MAX_COUNT, zero); // array of input handles
	handlesCount = 0;
	inputTypes = [];
	defaultActionSet = "";
	actionSets = {}; // struct of action set handles
	actionSetNames = [];
	spriteCache = {}; // struct of sprite paths
};

addSpriteGlyph = function(thePath) {
	if (!variable_struct_exists(spriteCache, thePath)) {
		// this is horrible
		spriteCache[$ thePath] = sprite_add(thePath, 1, false, false, 0, 0);
	}
	
	return spriteCache[$ thePath];
};

pushAction = function(actionSetName, actionName, isDigital) {
	var _hnd = isDigital
		? ParInput_GetDigitalActionHandle(actionName)
		: ParInput_GetAnalogActionHandle(actionName);
		
	actionSets[$ actionSetName].actions[$ actionName] = {
		handle: _hnd,
		digital: isDigital,
		name: isDigital
			? ParInput_GetStringForDigitalActionName(_hnd)
			: ParInput_GetStringForAnalogActionName(_hnd),
		data: [],
		origins: []
	};
	
	actionSets[$ actionSetName].names = variable_struct_get_names(actionSets[$ actionSetName].actions);
	actionSetNames = variable_struct_get_names(actionSets);
};

pushActionSet = function(actionSetName, isDefault) {
	actionSets[$ actionSetName] = {
		handle: ParInput_GetActionSetHandle(actionSetName),
		actions: {},
		names: []
	};
	
	if (isDefault) {
		defaultActionSet = actionSetName;
	}
};

activateActionSetLayer = function(deviceIndex, actionSetLayerName) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	var _actionSetLayer = actionSets[$ actionSetLayerName];
	ParInput_ActivateActionSetLayer(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex],
		_actionSetLayer.handle
	);
	return true;
};

deactivateActionSetLayer = function(deviceIndex, actionSetLayerName) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	var _actionSetLayer = actionSets[$ actionSetLayerName];
	ParInput_DeactivateActionSetLayer(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex],
		_actionSetLayer.handle
	);
	return true;
};

deactivateAllActionSetLayers = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	ParInput_DeactivateAllActionSetLayers(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex]
	);
	return true;
};

getActiveActionSetLayers = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	var _handles = []; // array of action set layer handles, will be filled with names
	ParInput_GetActiveActionSetLayers(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex],
		_handles
	);
	
	for (var _i = 0; _i < array_length(_handles); ++_i) {
		for (var _a = 0; _a < array_length(actionSetNames); ++_a) {
			var _name = actionSetNames[@ _a];
			if (actionSets[$ _name].handle == _handles[@ _i]) {
				// turn a handle element into a string name
				_handles[@ _i] = _name;
				break;
			}
		}
	}
	
	return _handles;
};

validDeviceIndex = function(deviceIndex) {
	return (
		!is_undefined(deviceIndex) &&
		(deviceIndex == allcons ||
			(deviceIndex >= 0 && deviceIndex < handlesCount))
	);
}

activateActionSet = function(deviceIndex, actionSetName) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	ParInput_ActivateActionSet(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex],
		actionSets[$ actionSetName].handle
	);
	
	return true;
};

refreshDevices = function() {
	//array_resize(handles, 0); // not great for performance, oh well...
	array_resize(inputTypes, 0);
	handlesCount = ParInput_GetConnectedControllers(handles);
	return handlesCount;
};

updateDevice = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	if (deviceIndex == allcons) {
		throw "\nupdateDevice() cannot be used with all controllers.";
	}
	
	var _myHandle = handles[@ deviceIndex]; // handle
	inputTypes[@ deviceIndex] = ParInput_GetInputTypeForHandle(_myHandle);
	var _actionSetName = getActionSet(deviceIndex); // struct
	
	if (is_undefined(_actionSetName)) {
		activateActionSet(deviceIndex, defaultActionSet);
		_actionSetName = getActionSet(deviceIndex);
	}
	
	var _actionSet = actionSets[$ _actionSetName];
	
	var _myActionSet = _actionSet.handle; // handle
	
	var _actionNames = _actionSet.names;
	for (var _i = 0; _i < array_length(_actionNames); ++_i) {
		var _actionName = _actionNames[@ _i];
		var _handleStruct = _actionSet.actions[$ _actionName];
		var _handle = _handleStruct.handle;
		
		var _data, _origins;
		_origins = [];
		if (_handleStruct.digital) {
			_data = ParInput_GetDigitalActionData(_myHandle, _handle);
			ParInput_GetDigitalActionOrigins(_myHandle, _myActionSet, _handle, _origins);
		}
		else {
			_data = ParInput_GetAnalogActionData(_myHandle, _handle);
			ParInput_GetAnalogActionOrigins(_myHandle, _myActionSet, _handle, _origins);
		}
		
		_handleStruct.data[@ deviceIndex] = _data;
		_handleStruct.origins[@ deviceIndex] = _origins;
	}
	
	return true;
};

deviceCount = function() {
	return handlesCount;
};

getActionSet = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return undefined;
	}
	
	var _myActionSet = ParInput_GetCurrentActionSet(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex]
	);
	
	for (var _i = 0; _i < array_length(actionSetNames); ++_i) {
		var _name = actionSetNames[@ _i];
		var _actionSet = actionSets[$ actionSetNames[@ _i]];
		if (_actionSet.handle == _myActionSet) {
			return _name;
		}
	}
	
	return undefined;
};

getActionData = function(deviceIndex, actionSetName, actionName) {
	if (!validDeviceIndex(deviceIndex)) {
		return undefined;
	}
	
	if (deviceIndex == allcons) {
		throw "\ngetActionData cannot be used with all controllers, pick one.";
	}
	
	return actionSets[$ actionSetName].actions[$ actionName].data[@ deviceIndex];
};

getActionUIData = function(deviceIndex, actionSetName, actionName) {
	if (!validDeviceIndex(deviceIndex)) {
		return undefined;
	}
	
	if (deviceIndex == allcons) {
		throw "\ngetActionUIData cannot be used with all controllers, pick one.";
	}
	
	var _action = actionSets[$ actionSetName].actions[$ actionName];
	var _origins = _action.origins[@ deviceIndex];
	var _retstruct = {
		locname: _action.name,
		buttons: []
	};
	
	for (var _i = 0; _i < array_length(_origins); ++_i) {
		var _origin = _origins[@ _i];
		var _path = ParInput_GetGlyphPNGForActionOrigin(_origin, ESteamInputGlyphSize.k_Small, 0);
		var _spr = addSpriteGlyph(_path);
		
		var _btnstruct = {
			raworigin: _origin,
			name: ParInput_GetStringForActionOrigin(_origin),
			spr: _spr
		};
		
		array_push(_retstruct.buttons, _btnstruct);
	}
	
	return _retstruct;
};

getInputType = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return undefined;
	}
	
	if (deviceIndex == allcons) {
		throw "\ngetInputType cannot be used with all controllers, pick one.";
	}
	
	return inputTypes[@ deviceIndex];
};

update = function() {
	refreshDevices();
	
	for (var _i = 0; _i < handlesCount; ++_i) {
		updateDevice(_i);
	}
	
	return handlesCount;
};

showBindingPanel = function(deviceIndex) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	ParInput_ShowBindingPanel(
		(deviceIndex == allcons)
		? allcons
		: handles[@ deviceIndex]
	);
	
	return true;
};

init = function() {
	internalInit();
	
	pushActionSet("MenuControls", /*isDefault?*/true);
	//{
	pushAction("MenuControls", "menu_up", /*isDigital?*/true);
	pushAction("MenuControls", "menu_down", /*isDigital?*/true);
	pushAction("MenuControls", "menu_left", /*isDigital?*/true);
	pushAction("MenuControls", "menu_right", /*isDigital?*/true);
	pushAction("MenuControls", "menu_select", /*isDigital?*/true);
	pushAction("MenuControls", "menu_cancel", /*isDigital?*/true);
	pushAction("MenuControls", "pause_menu", /*isDigital?*/true);
	//}
	
	pushActionSet("InGameControls", /*isDefault?*/false);
	//{
	pushAction("InGameControls", "Move", /*isDigital?*/false);
	pushAction("InGameControls", "Camera", /*isDigital?*/false);
	pushAction("InGameControls", "Throttle", /*isDigital?*/false);
	pushAction("InGameControls", "fire", /*isDigital?*/true);
	pushAction("InGameControls", "Jump", /*isDigital?*/true);
	pushAction("InGameControls", "pause_menu", /*isDigital?*/true);
	//}
	
	update();
};

destroy = function() {
	var _sprites = variable_struct_get_names(spriteCache);
	for (var _i = 0; _i < array_length(_sprites); ++_i) {
		var _spr = spriteCache[$ _sprites[@ _i]];
		if (sprite_exists(_spr)) {
			sprite_delete(_spr);
			_spr = -1;
		}
	}
};

init();

// -- not actually a part of the Steam Input API, just convenient format functions -- //

formatAnalog = function(dataStruct) {
	return
		"x:" + string(dataStruct.x) +
		",y:" + string(dataStruct.y) +
		",active:" + (dataStruct.bActive? "true": "false") +
		",mode:" + string(dataStruct.eMode);
};

formatDigital = function(dataStruct) {
	return
		"state:" + (dataStruct.bState? "true": "false") +
		",active:" + (dataStruct.bActive? "true": "false");
};

vibraHelper = function(deviceIndex, ls, rs) {
	if (!validDeviceIndex(deviceIndex)) {
		return false;
	}
	
	var _hnd = (deviceIndex == allcons) ? allcons : handles[@ deviceIndex];
	ParInput_TriggerVibration(_hnd, ls, rs);
	return true;
};

_d = 0;
vflag = false;

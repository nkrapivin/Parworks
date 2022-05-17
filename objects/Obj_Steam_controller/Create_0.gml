
// With this function you can create a new leaderboard for your game.
// This call just assures we have a leaderboard to work with for later calls.

randomize();
steam_set_warning_message_hook();

#macro SteamLeaderboard "YYLeaderboard_10/29/21--"

// a small test to see if Steam launch parameters are passed to the game...
var _paramcnt = parameter_count();
for (var _i = 1; _i < _paramcnt; ++_i) {
	var _param = string(parameter_string(_i));
	if (_param == "-dodebugoverlay") {
		show_debug_overlay(true);
	}
}

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

Par_AttachTo(
	EParCallbackFunction.k_OnRemoteStorageLocalFileChange,
	function(pParam, userData = undefined) {
		var _count = ParRemoteStorage_GetLocalFileChangeCount();
		show_debug_message("OnRemoteStorageLocalFileChange: count=" + string(_count));
		
		for (var _i = 0; _i < _count; ++_i) {
			var _changeTypeRef = {}; // must be empty structs with no members, `refval` will be added.
			var _filePathTypeRef = {};
			
			//string
			var _filePath = ParRemoteStorage_GetLocalFileChange(_i, _changeTypeRef, _filePathTypeRef);
			//ERemoteStorageLocalFileChange
			var _changeType = _changeTypeRef.refval;
			//ERemoteStorageFilePathType
			var _filePathType = _filePathTypeRef.refval;
			
			show_debug_message(
				"[" + string(_i) + "] - path='" + _filePath +
				"'" + ",changeType=" + string(_changeType) +
				",filePathType=" + string(_filePathType)
			);
			
			// feel free to reload the files here:
			//....
		}
		
		show_debug_message("OnRemoteStorageLocalFileChange: end");
	}
);


// initialize Steam Input:
var _ok = ParInput_Init(false);
show_debug_message("ParInput_Init(): " + string(_ok));
if (!_ok)
	throw "\nUnable to initialize Parworks or ParInput";
	
ParInput_EnableDeviceCallbacks();

if (ParUtils_IsSteamInBigPictureMode()) {
	window_set_fullscreen(true);
}

room_goto(Room_Steam_Main);


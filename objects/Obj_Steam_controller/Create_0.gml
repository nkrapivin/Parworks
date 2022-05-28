
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


var _filteredRef = {}; // .refval = <result>
var _msg = "kek kok you dolboeb";
var _msglen = string_byte_length(_msg) + 1;
var _bInit = ParUtils_InitFilterText(0);
var _wrote = ParUtils_FilterText(
	ETextFilteringContext.k_GameContent,
	steam_get_user_steam_id(),
	_msg,
	_filteredRef,
	_msglen
);

var _kek = "Hello meow meow!";
var _buff = buffer_create(string_byte_length(_kek) + 1, buffer_fixed, 1);
buffer_write(_buff, buffer_string, _kek);

Par_AttachToCallResult(
	ParUser_RequestEncryptedAppTicket(buffer_get_address(_buff), buffer_get_size(_buff)),
	function(pCallback, bIOFailure) {
		if (bIOFailure) {
			return false;
		}
		
		var _sizeRef = {};
		ParUser_GetEncryptedAppTicket(ptr(pointer_null), 0, _sizeRef);
		var _size = _sizeRef.refval;
		var _buff = buffer_create(_size, buffer_fixed, 1);
		ParUser_GetEncryptedAppTicket(buffer_get_address(_buff), _size, _sizeRef);
		
		buffer_delete(_buff);
		return true;
		var _sock = network_create_socket(network_socket_tcp);
		network_connect_raw(_sock, "127.0.0.1", 42069);
		
		var _netbuff = buffer_create(buffer_sizeof(buffer_u32) + buffer_get_size(_buff), buffer_fixed, 1);
		buffer_write(_netbuff, buffer_u32, _size);
		buffer_copy(_buff, 0, buffer_get_size(_buff), _netbuff, buffer_sizeof(buffer_u32));
		network_send_raw(_sock, _netbuff, buffer_get_size(_netbuff));
		
		// wait a reply from a server:
		/*
		var _serverBuff = async_load[? "buffer"];
		var _steamId = buffer_read(_serverBuff, buffer_u64);
		var _appId = buffer_read(_serverBuff, buffer_u32);
		var _issueTime = buffer_read(_serverBuff, buffer_u32); // in UNIX time
		var _issueTimeGM = (_issueTime == 0) ? 0 : (((_issueTime + 0.5) / 86400) + 25569);
		var _flags = buffer_read(_serverBuff, buffer_u32);
		var _userDataLen = buffer_read(_serverBuff, buffer_u32);
		var _valid =
			_steamId != int64("0") &&
			_appId == ParUtils_GetAppID() &&
			_issueTime != 0 &&
			_userDataLen != 0;
		// read user data...
		*/
		
		return true;
	},
	undefined
);

//show_message(Par_GMTimeToRTime(Par_RTimeToGMTime(1653398292)) == 1653398292);
show_debug_message("bInit: " + string(_bInit));
show_debug_message("wrote: " + string(_wrote));
show_debug_message("Filtered text: " + _filteredRef.refval);

room_goto(Room_Steam_Main);



/// @desc Converts Steam UNIX Epoch time to GameMaker time
/// @param RTimeValue RTime32 argument or similar
/// @returns GameMaker datetime_* value
function Par_RTimeToGMTime(RTimeValue) {
	// an exact replica of YoYo's linux time -> gm time function
	return (((real(RTimeValue) + 0.5) / 86400.0) + 25569.0);
}

/// @desc Converts GameMaker datetime_* value into Steam RTime32
/// @param GMTimeValue datetime_* value
/// @returns RTime32 value
function Par_GMTimeToRTime(GMTimeValue) {
	// the inverse of Par_RTimeToGMTime
	return round(((GMTimeValue - 25569.0) * 86400.0) - 0.5);
}


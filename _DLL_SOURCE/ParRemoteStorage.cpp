#include "Par.h"
#include "ParGM.h"

funcdef(ParRemoteStorage_BeginFileWriteBatch) {
	Result = RValue{
		SteamRemoteStorage()->BeginFileWriteBatch()
	};
}

funcdef(ParRemoteStorage_EndFileWriteBatch) {
	Result = RValue{
		SteamRemoteStorage()->EndFileWriteBatch()
	};
}

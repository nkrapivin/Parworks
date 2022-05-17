#include "Par.h"
#include "ParGM.h"

funcdef(ParRemoteStorage_GetLocalFileChangeCount) {
	Result = RValue{
		SteamRemoteStorage()->GetLocalFileChangeCount()
	};
}

funcdef(ParRemoteStorage_GetLocalFileChange) {
	ensureargc(3);
	ensurekind(1, eRVK_OBJECT);
	ensurekind(2, eRVK_OBJECT);

	ERemoteStorageLocalFileChange changeType{};
	ERemoteStorageFilePathType filePathType{};

	auto filepath{
		SteamRemoteStorage()->GetLocalFileChange(
			ParGM()->YYGetInt32(argument, 0),
			&changeType,
			&filePathType
		)
	};

	ParGM()->StructAddInt(&argument[1], "refval", parcast<int>(changeType));
	ParGM()->StructAddInt(&argument[2], "refval", parcast<int>(filePathType));

	ParGM()->YYCreateString(
		&Result,
		filepath
	);
}

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

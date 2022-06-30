#pragma once
//
// Copyright (C) 2020 Opera Norway AS. All rights reserved.
//
// This file is an original work developed by Opera.
//

#include <cstdint>

enum eBuffer_Format {
	eBuffer_Format_Fixed = 0,
	eBuffer_Format_Grow = 1,
	eBuffer_Format_Wrap = 2,
	eBuffer_Format_Fast = 3,
	eBuffer_Format_VBuffer = 4,
	eBuffer_Format_Network = 5,
};

enum eRVKind : unsigned {
	eRVK_REAL = 0,		// Real value
	eRVK_STRING = 1,		// String value
	eRVK_ARRAY = 2,		// Array value
	eRVK_OBJECT = 6,		// YYObjectBase* value 
	eRVK_INT32 = 7,		// Int32 value
	eRVK_UNDEFINED = 5,	// Undefined value
	eRVK_PTR = 3,		// Ptr value
	eRVK_VEC3 = 4,		// Deprecated : unused : Vec3 (x,y,z) value (within the RValue)
	eRVK_VEC4 = 8,		// Deprecated : unused :Vec4 (x,y,z,w) value (allocated from pool)
	eRVK_VEC44 = 9,		// Deprecated : unused :Vec44 (matrix) value (allocated from pool)
	eRVK_INT64 = 10,		// Int64 value
	eRVK_ACCESSOR = 11,	// Actually an accessor
	eRVK_NULL = 12,		// JS Null
	eRVK_BOOL = 13,		// Bool value
	eRVK_ITERATOR = 14,	// JS For-in Iterator
	eRVK_REF = 15,		// Reference value (uses the ptr to point at a RefBase structure)
	eRVK_UNSET = 0x0ffffff
};

inline const char* eRVKindToString(eRVKind kind) {
	switch (kind) {
		case eRVKind::eRVK_REAL: return "real";
		case eRVKind::eRVK_STRING: return "string";
		case eRVKind::eRVK_ARRAY: return "array";
		case eRVKind::eRVK_PTR: return "pointer";
		case eRVKind::eRVK_VEC3: return "vec3";
		case eRVKind::eRVK_UNDEFINED: return "undefined";
		case eRVKind::eRVK_OBJECT: return "struct";
		case eRVKind::eRVK_INT32: return "int32";
		case eRVKind::eRVK_VEC4: return "vec4";
		case eRVKind::eRVK_VEC44: return "matrix";
		case eRVKind::eRVK_INT64: return "int64";
		case eRVKind::eRVK_ACCESSOR: return "accessor";
		case eRVKind::eRVK_NULL: return "null";
		case eRVKind::eRVK_BOOL: return "bool";
		case eRVKind::eRVK_ITERATOR: return "iterator";
		case eRVKind::eRVK_REF: return "ref";
		case eRVKind::eRVK_UNSET: return "unset";
		default: return "unknown";
	}
}

class YYObjectBase;
class CInstance;
class CScriptRef;
class RefDynamicArrayOfRValue;

struct YYRunnerInterface;
extern const YYRunnerInterface* ParGM();

struct HTTP_REQ_CONTEXT;
struct RValue;
typedef int (*PFUNC_async)(HTTP_REQ_CONTEXT* _pContext, void* _pPayload, int* _pMap);
typedef void (*PFUNC_cleanup)(HTTP_REQ_CONTEXT* _pContext);
typedef void (*PFUNC_process)(HTTP_REQ_CONTEXT* _pContext);

typedef void (*TSetRunnerInterface)(const YYRunnerInterface* pRunnerInterface, size_t _functions_size);
typedef void (*TYYBuiltin)(RValue& Result, CInstance* selfinst, CInstance* otherinst, int argc, RValue* arg);
typedef RValue& (*TYYCCall)(CInstance* selfinst, CInstance* otherinst, RValue& Result, int argc, RValue** args);

typedef void* HYYMUTEX;
typedef void* HSPRITEASYNC;

struct YYRunnerInterface {
	// basic interaction with the user
	void (*DebugConsoleOutput)(const char* fmt, ...); // hook to YYprintf
	void (*ReleaseConsoleOutput)(const char* fmt, ...);
	void (*ShowMessage)(const char* msg);

	// for printing error messages
	void (*YYError)(const char* _error, ...);

	// alloc, realloc and free
	void* (*YYAlloc)(int _size);
	void* (*YYRealloc)(void* pOriginal, int _newSize);
	void  (*YYFree)(const void* p);
	const char* (*YYStrDup)(const char* _pS);

	// yyget* functions for parsing arguments out of the arg index
	bool (*YYGetBool)(const RValue* _pBase, int _index);
	float (*YYGetFloat)(const RValue* _pBase, int _index);
	double (*YYGetReal)(const RValue* _pBase, int _index);
	int32_t(*YYGetInt32)(const RValue* _pBase, int _index);
	uint32_t(*YYGetUint32)(const RValue* _pBase, int _index);
	long long(*YYGetInt64)(const RValue* _pBase, int _index);
	void* (*YYGetPtr)(const RValue* _pBase, int _index);
	intptr_t(*YYGetPtrOrInt)(const RValue* _pBase, int _index);
	const char* (*YYGetString)(const RValue* _pBase, int _index);

	// typed get functions from a single rvalue
	bool (*BOOL_RValue)(const RValue* _pValue);
	double (*REAL_RValue)(const RValue* _pValue);
	void* (*PTR_RValue)(const RValue* _pValue);
	long long(*INT64_RValue)(const RValue* _pValue);
	int32_t(*INT32_RValue)(const RValue* _pValue);

	// calculate hash values from an RValue
	int (*HASH_RValue)(const RValue* _pValue);

	// copying, setting and getting RValue
	void (*SET_RValue)(RValue* _pDest, RValue* _pV, YYObjectBase* _pPropSelf, int _index);
	bool (*GET_RValue)(RValue* _pRet, RValue* _pV, YYObjectBase* _pPropSelf, int _index, bool fPrepareArray, bool fPartOfSet);
	void (*COPY_RValue)(RValue* _pDest, const RValue* _pSource);
	int (*KIND_RValue)(const RValue* _pValue);
	void (*FREE_RValue)(RValue* _pValue);
	void (*YYCreateString)(RValue* _pVal, const char* _pS);

	void (*YYCreateArray)(RValue* pRValue, int n_values, const double* values);

	// finding and runnine user scripts from name
	int (*Script_Find_Id)(const char* name);
	bool (*Script_Perform)(int ind, CInstance* selfinst, CInstance* otherinst, int argc, RValue* res, RValue* arg);

	// finding builtin functions
	bool  (*Code_Function_Find)(const char* name, int* ind);

	// http functions
	void (*HTTP_Get)(const char* _pFilename, int _type, PFUNC_async _async, PFUNC_cleanup _cleanup, void* _pV);
	void (*HTTP_Post)(const char* _pFilename, const char* _pPost, PFUNC_async _async, PFUNC_cleanup _cleanup, void* _pV);
	void (*HTTP_Request)(const char* _url, const char* _method, const char* _headers, const char* _pBody, PFUNC_async _async, PFUNC_cleanup _cleanup, void* _pV, int _contentLength);

	// sprite loading helper functions
	int (*ASYNCFunc_SpriteAdd)(HTTP_REQ_CONTEXT* _pContext, void* _p, int* _pMap);
	void (*ASYNCFunc_SpriteCleanup)(HTTP_REQ_CONTEXT* _pContext);
	HSPRITEASYNC(*CreateSpriteAsync)(int* _pSpriteIndex, int _xOrig, int _yOrig, int _numImages, int _flags);

	// timing
	long long(*Timing_Time)(void);
	void (*Timing_Sleep)(long long slp, bool precise);

	// mutex handling
	HYYMUTEX(*YYMutexCreate)(const char* _name);
	void (*YYMutexDestroy)(HYYMUTEX hMutex);
	void (*YYMutexLock)(HYYMUTEX hMutex);
	void (*YYMutexUnlock)(HYYMUTEX hMutex);

	// ds map manipulation for 
	void (*CreateAsyncEventWithDSMap)(int _map, int _event);
	void (*CreateAsyncEventWithDSMapAndBuffer)(int _map, int _buffer, int _event);
	int (*CreateDsMap)(int _num, ...);

	bool (*DsMapAddDouble)(int _index, const char* _pKey, double value);
	bool (*DsMapAddString)(int _index, const char* _pKey, const char* pVal);
	bool (*DsMapAddInt64)(int _index, const char* _pKey, long long value);

	// buffer access
	bool (*BufferGetContent)(int _index, void** _ppData, int* _pDataSize);
	int (*BufferWriteContent)(int _index, int _dest_offset, const void* _pSrcMem, int _size, bool _grow, bool _wrap);
	int (*CreateBuffer)(int _size, eBuffer_Format _bf, int _alignment);

	// variables
	volatile bool* pLiveConnection;
	int* pHTTP_ID;

	int (*DsListCreate)();
	void (*DsMapAddList)(int _dsMap, const char* _key, int _listIndex);
	void (*DsListAddMap)(int _dsList, int _mapIndex);
	void (*DsMapClear)(int _dsMap);
	void (*DsListClear)(int _dsList);

	bool (*BundleFileExists)(const char* _pszFileName);
	bool (*BundleFileName)(char* _name, int _size, const char* _pszFileName);
	bool (*SaveFileExists)(const char* _pszFileName);
	bool (*SaveFileName)(char* _name, int _size, const char* _pszFileName);

	bool (*Base64Encode)(const void* input_buf, size_t input_len, void* output_buf, size_t output_len);

	void (*DsListAddInt64)(int _dsList, long long _value);

	void (*AddDirectoryToBundleWhitelist)(const char* _pszFilename);
	void (*AddFileToBundleWhitelist)(const char* _pszFilename);
	void (*AddDirectoryToSaveWhitelist)(const char* _pszFilename);
	void (*AddFileToSaveWhitelist)(const char* _pszFilename);

	const char* (*KIND_NAME_RValue)(const RValue* _pV);

	void (*DsMapAddBool)(int _index, const char* _pKey, bool value);
	void (*DsMapAddRValue)(int _index, const char* _pKey, RValue* value);
	void (*DestroyDsMap)(int _index);

	void (*StructCreate)(RValue* _pStruct);
	void (*StructAddBool)(RValue* _pStruct, const char* _pKey, bool _value);
	void (*StructAddDouble)(RValue* _pStruct, const char* _pKey, double _value);
	void (*StructAddInt)(RValue* _pStruct, const char* _pKey, int _value);
	void (*StructAddRValue)(RValue* _pStruct, const char* _pKey, RValue* _pValue);
	void (*StructAddString)(RValue* _pStruct, const char* _pKey, const char* _pValue);
};

#pragma pack(push, 4)
struct RValue {
	union {
		int v32;
		long long v64;
		unsigned long long vu64;
		double val;
		void* ptr;
		uintptr_t ptr_as_num;
		RefDynamicArrayOfRValue* arr;
		YYObjectBase* obj;
		CScriptRef* scref;
		CInstance* instptr;
	};

	unsigned flags;
	unsigned kind;

	RValue() : v64{ 0 }, flags{ 0 }, kind{ eRVK_UNDEFINED } {};
	explicit RValue(bool v) : val{ v ? 1.0 : 0.0 }, flags{ 0 }, kind{ eRVK_BOOL } {};
	explicit RValue(int v) : val{ parcast<double>(v) }, flags{ 0 }, kind{ eRVK_REAL } {};
	explicit RValue(unsigned int v) : val{ parcast<double>(v) }, flags{ 0 }, kind{ eRVK_REAL } {};
	explicit RValue(float v) : val{ v }, flags{ 0 }, kind{ eRVK_REAL } {};
	explicit RValue(double v) : val{ v }, flags{ 0 }, kind{ eRVK_REAL } {};
	explicit RValue(long long v) : v64{ v }, flags{ 0 }, kind{ eRVK_INT64 } {};
	explicit RValue(unsigned long long v) : vu64{ v }, flags{ 0 }, kind{ eRVK_INT64 } {
		// yes I know this is kinda wrong, but I want to be sure here...
	};
	explicit RValue(YYObjectBase* v) : obj{ v }, flags{ 0 }, kind{ eRVK_OBJECT } {};
	explicit RValue(CInstance* v) : instptr{ v }, flags{ 0 }, kind{ eRVK_OBJECT } {};
	explicit RValue(void* v) : ptr{ v }, flags{ 0 }, kind{ eRVK_PTR } {};
	//explicit RValue(void* v) : ptr{ v }, flags{ 0 }, kind{ eRVK_PTR } {};

	inline unsigned typeOf() const { return kind & eRVK_UNSET; }
	inline const char* nameOf() const { return eRVKindToString(parcast<eRVKind>(typeOf())); }

	inline RValue(const RValue& other) : v64{ 0 }, flags{ 0 }, kind{ eRVK_UNDEFINED } {
		if (this != &other) {
			ParGM()->COPY_RValue(this, &other);
		}
	}

	inline RValue& operator=(const RValue& other) {
		if (this != &other) {
			ParGM()->COPY_RValue(this, &other);
		}

		return *this;
	}

	~RValue() {
		ParGM()->FREE_RValue(this);
	}
};
#pragma pack(pop)

class CWeakRef;

class CInstanceBase {
public:
	RValue* yyvars; // legacy always nullptr
	virtual ~CInstanceBase() = 0;
	virtual RValue& InternalGetYYVarRef(int index) = 0;
	virtual RValue& InternalGetYYVarRefL(int index) = 0;
};

class YYObjectBase : public CInstanceBase {
public:
	YYObjectBase* m_pNextObject;
	YYObjectBase* m_pPrevObject;
	YYObjectBase* m_prototype;
	const char* m_class;
	void* m_getOwnProperty;
	void* m_deleteProperty;
	void* m_defineOwnProperty;
	void* m_yyvarsMap;
	CWeakRef** m_pWeakRefs;
	unsigned m_numWeakRefs;
	unsigned m_nvars;
	unsigned m_flags;
	unsigned m_capacity;
	unsigned m_visited;
	unsigned m_visitedGC;
	int m_GCgen;
	int m_GCcreationframe;
	int m_slot;
	int m_kind;
	int m_rvalueInitType;
	int m_curSlot;
};

class CWeakRef : public YYObjectBase {
public:
	YYObjectBase* pWeakRef;
};

class RefDynamicArrayOfRValue : public YYObjectBase {
public:
	int refcount;
	int flags;
	RValue* pArray;
	long long owner;
	int visited;
	int length;
};

class CScriptRef : public YYObjectBase {
public:
	void* m_callScript;
	TYYBuiltin m_callCpp;
	TYYCCall m_callYYC;
	RValue m_scope;
	RValue m_boundThis;
	YYObjectBase* m_pStatic;
	void* m_hasInstance;
	void* m_construct;
	const char* m_tag;
};

class CInstance : public YYObjectBase {
public:
	// hell no.
};

extern TYYBuiltin F_ScriptExecute;
extern YYObjectBase* g_pGlobal;

class CDisableCoW {

private:

	RefDynamicArrayOfRValue* m_pRefArray;

	int m_iOldRefCount;

public:

	CDisableCoW(RefDynamicArrayOfRValue* pRefArray) : m_pRefArray{ pRefArray }, m_iOldRefCount{ pRefArray ? pRefArray->refcount : 0 } {
		// will set the refcount to 1 (prevent CoW) and set it back once destructed.
		if (m_pRefArray) {
			m_pRefArray->refcount = 1;
		}
	};

	~CDisableCoW() {
		if (m_pRefArray) {
			m_pRefArray->refcount = m_iOldRefCount;
		}
	}

};

#define funcdef(_FunctionName) parex void _FunctionName \
	(RValue& Result, CInstance* pSelf, CInstance* pOther, int argument_count, RValue* argument)

#define ensureargc(_ExpectedArgC) if (argument_count < _ExpectedArgC    ) \
	{ ParGM()->YYError("%s expected %d arguments got %d.", __FUNCTION__, _ExpectedArgC, argument_count); }

#define ensurekind(_Index, _Type) if (argument[_Index].typeOf() != _Type) \
	{ ParGM()->YYError("%s invalid argument[%d] type expected %s got %s.", __FUNCTION__, _Index, eRVKindToString(_Type), argument[_Index].nameOf()); }

#define ensureiptr(_InterfacePtr) if (!                  (_InterfacePtr)) \
	{ Result = RValue{ }; /* return `undefined` */ return; }


//#define disablecow(_Index) CDisableCoW _CDisableCoW_ ## _Index { (&(argument[_Index].arr)) }

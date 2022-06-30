#include "Par.h"
#include "ParGM.h"
#include <array>
#include <utility>

static int g_GetInstanceId{ -1 };
static int g_MethodGetIndexId{ -1 };
static int g_MethodGetSelfId{ -1 };

static void Par_EnsureFunctionResolved(int& outResult, const char* name) {
	if (outResult < 0) {
		if (!ParGM()->Code_Function_Find(name, &outResult)) {
			ParGM()->YYError("%s unable to resolve required function %s", __FUNCTION__, name, 0);
			return;
		}
	}
}

static YYObjectBase* Par_InstanceFromId(const RValue& instidArgument, CInstance* callerSelf, CInstance* callerOther) {
	Par_EnsureFunctionResolved(g_GetInstanceId, "@@GetInstance@@");

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ g_GetInstanceId }, RValue{ instidArgument } };

	F_ScriptExecute(
		res,
		callerSelf,
		callerOther,
		parcast<int>(args.size()),
		args.data()
	);

	return res.obj;
}

static std::pair<int, RValue> Par_GetMethodPair(const RValue& mtArgument, CInstance* callerSelf, CInstance* callerOther) {
	Par_EnsureFunctionResolved(g_MethodGetIndexId, "method_get_index");
	Par_EnsureFunctionResolved(g_MethodGetSelfId, "method_get_self");

	std::pair<int, RValue> retpair{ };
	RValue res{ };
	std::array<RValue, 2> args{ RValue{ g_MethodGetIndexId }, RValue{ mtArgument } };

	F_ScriptExecute(
		res,
		callerSelf,
		callerOther,
		parcast<int>(args.size()),
		args.data()
	);

	if (res.typeOf() == eRVK_UNDEFINED) {
		ParGM()->YYError("%s method index is undefined, this should not happen.", __FUNCTION__);
	}

	retpair.first = ParGM()->INT32_RValue(&res);

	args = std::array<RValue, 2>{ RValue{ g_MethodGetSelfId }, RValue{ mtArgument } };

	F_ScriptExecute(
		res,
		callerSelf,
		callerOther,
		parcast<int>(args.size()),
		args.data()
	);

	// if return value is pointer_null then return `self`
	if (res.typeOf() == eRVK_UNDEFINED || (res.typeOf() == eRVK_PTR && !res.ptr)) {
		res = RValue{ callerSelf };
	}

	retpair.second = res;

	return retpair;
}

class CParCallResultHandlerBase {
public:

	virtual void CancelThis() = 0;

	virtual bool IsThisActive() = 0;

	virtual void SetThisGameserverFlag() = 0;
};

template<class T>
class CParCallResultHandler : public CParCallResultHandlerBase {
	SteamAPICall_t m_hCall;
	int m_iScriptIndex;
	int m_iDSMapIndex;
	YYObjectBase* m_pSelf;
	CCallResult<CParCallResultHandler, T> m_CallResult;

	template<class TT>
	void DeserializeCallResult(RValue& Result, TT* pCallback); // implemented for every known CallResult type down below:

	template<>
	void DeserializeCallResult<EncryptedAppTicketResponse_t>(RValue& Result, EncryptedAppTicketResponse_t* pCallback) {
		if (!pCallback) {
			return;
		}

		RValue iCallback{ pCallback->k_iCallback };
		RValue eResult{ pCallback->m_eResult };

		ParGM()->StructCreate(&Result);
		ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
		ParGM()->StructAddRValue(&Result, "m_eResult", &eResult);
	}

	template<>
	void DeserializeCallResult<StoreAuthURLResponse_t>(RValue& Result, StoreAuthURLResponse_t* pCallback) {
		if (!pCallback) {
			return;
		}

		RValue iCallback{ pCallback->k_iCallback };

		ParGM()->StructCreate(&Result);
		ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
		ParGM()->StructAddString(&Result, "m_szURL", pCallback->m_szURL);
	}

	template<>
	void DeserializeCallResult<MarketEligibilityResponse_t>(RValue& Result, MarketEligibilityResponse_t* pCallback) {
		if (!pCallback) {
			return;
		}

		RValue iCallback{ pCallback->k_iCallback };
		RValue bAllowed{ pCallback->m_bAllowed };
		RValue eNotAllowedReason{ pCallback->m_eNotAllowedReason };
		RValue rtAllowedAtTime{ pCallback->m_rtAllowedAtTime };
		RValue cdaySteamGuardRequiredDays{ pCallback->m_cdaySteamGuardRequiredDays };
		RValue cdayNewDeviceCooldown{ pCallback->m_cdayNewDeviceCooldown };

		ParGM()->StructCreate(&Result);
		ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
		ParGM()->StructAddRValue(&Result, "m_bAllowed", &bAllowed);
		ParGM()->StructAddRValue(&Result, "m_eNotAllowedReason", &eNotAllowedReason);
		ParGM()->StructAddRValue(&Result, "m_rtAllowedAtTime", &rtAllowedAtTime);
		ParGM()->StructAddRValue(&Result, "m_cdaySteamGuardRequiredDays", &cdaySteamGuardRequiredDays);
		ParGM()->StructAddRValue(&Result, "m_cdayNewDeviceCooldown", &cdayNewDeviceCooldown);
	}

	template<>
	void DeserializeCallResult<DurationControl_t>(RValue& Result, DurationControl_t* pCallback) {
		if (!pCallback) {
			return;
		}

		RValue iCallback{ pCallback->k_iCallback };
		RValue eResult{ pCallback->m_eResult };
		RValue appid{ pCallback->m_appid };
		RValue bApplicable{ pCallback->m_bApplicable };
		RValue csecsLast5h{ pCallback->m_csecsLast5h };
		RValue progress{ pCallback->m_progress };
		RValue notification{ pCallback->m_notification };
		RValue csecsToday{ pCallback->m_csecsToday };
		RValue csecsRemaining{ pCallback->m_csecsRemaining };

		ParGM()->StructCreate(&Result);
		ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
		ParGM()->StructAddRValue(&Result, "m_eResult", &eResult);
		ParGM()->StructAddRValue(&Result, "m_appid", &appid);
		ParGM()->StructAddRValue(&Result, "m_bApplicable", &bApplicable);
		ParGM()->StructAddRValue(&Result, "m_csecsLast5h", &csecsLast5h);
		ParGM()->StructAddRValue(&Result, "m_progress", &progress);
		ParGM()->StructAddRValue(&Result, "m_notification", &notification);
		ParGM()->StructAddRValue(&Result, "m_csecsToday", &csecsToday);
		ParGM()->StructAddRValue(&Result, "m_csecsRemaining", &csecsRemaining);
	}

	void OnCallResultFunction(T* pCallback, bool bIOFailure) {
		// can happen if stuff is VERY broken......
		if (!this) {
			return;
		}

		ESteamAPICallFailure failReason{ SteamUtils()->GetAPICallFailureReason(m_hCall) };

		RValue res{ };

		RValue callStruct{ };
		if (pCallback) {
			DeserializeCallResult(callStruct, pCallback);
		}
		
		std::array<RValue, 5> args{ RValue{ m_iScriptIndex }, RValue{ callStruct }, RValue{ bIOFailure }, RValue{ m_hCall }, RValue{ failReason } };

		F_ScriptExecute(
			res,
			parcast<CInstance*>(m_pSelf ? m_pSelf : g_pGlobal),
			parcast<CInstance*>(m_pSelf ? m_pSelf : g_pGlobal),
			parcast<int>(args.size()),
			args.data()
		);

		// must be the last line in this function
		delete this;
	}

public:

	~CParCallResultHandler() {
		m_hCall = k_uAPICallInvalid;
		m_iScriptIndex = -1;
		if (m_pSelf) {
			ParGM()->DestroyDsMap(m_iDSMapIndex);
		}
		m_iDSMapIndex = -1;
		m_pSelf = nullptr;
		// m_CallResult is autodestructed by valve's destructor.
	}

	CParCallResultHandler(SteamAPICall_t hCall, const RValue& rvMethod, const RValue& rvSelf, CInstance* callerSelf, CInstance* callerOther) {
		m_hCall = hCall;
		m_iScriptIndex = -1;
		m_iDSMapIndex = -1;

		RValue realSelf{ rvSelf };

		if (rvMethod.typeOf() == eRVK_OBJECT) {
			auto p{ Par_GetMethodPair(rvMethod, callerSelf, callerOther) };
			m_iScriptIndex = p.first;
			// method self logic
			// if method has a self, use that, if not, use caller's self
			realSelf = p.second.typeOf() == eRVK_UNDEFINED ? RValue{ callerSelf } : p.second;
		}
		else {
			m_iScriptIndex = ParGM()->INT32_RValue(&rvMethod);
		}

		if (realSelf.typeOf() == eRVK_UNDEFINED) {
			// use caller's self if passed self is undefined
			m_pSelf = callerSelf;
		}
		else if (realSelf.typeOf() == eRVK_OBJECT) {
			// raw instance or struct pointer
			m_pSelf = realSelf.obj;
		}
		else {
			// a number, maybe an instance id?
			m_pSelf = Par_InstanceFromId(realSelf, callerSelf, callerOther);
			realSelf = RValue{ m_pSelf };
		}

		if (m_pSelf) {
			m_iDSMapIndex = ParGM()->CreateDsMap(0);
			// to prevent garbage collection:
			ParGM()->DsMapAddRValue(m_iDSMapIndex, "ParCallResultSelf", &realSelf);
		}

		m_CallResult.Set(m_hCall, this, &CParCallResultHandler::OnCallResultFunction);
	}

	virtual void CancelThis() override {
		// the reason why I check if this!=nullptr is because this can be called in GML side
		if (this) {
			delete this; // deleting this class will cancel the CallResult as well.
		}
	}

	virtual bool IsThisActive() override {
		if (this) {
			return m_CallResult.IsActive();
		}

		return false;
	}

	virtual void SetThisGameserverFlag() override {
		if (this) {
			m_CallResult.SetGameserverFlag();
		}
	}
};

funcdef(ParCallResult_OnEncryptedAppTicketResponse) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	// arg0 must be int64 (SteamAPICall_t)
	// arg1 can be either number (script index) or YYObjectBase* (method)
	// arg2 can be either undefined, struct, or an instance id
	// (hSteamAPICall, onMethodOrScript, callSelf)
	
	auto pCR{ new CParCallResultHandler<EncryptedAppTicketResponse_t>(
		// api call handle
		parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)),
		// method or script index, if method and method's self isn't undefined, will use that instead of arg2
		// (even if arg2 is a different self, method's self will be used instead as that's GML semantics)
		argument[1],
		// the `self` for function, either instance id, or struct, or undefined (will use ParGlobal)
		(argument_count > 2) ? argument[2] : RValue{ },
		// used if a gml method is provided and it is nullptr (static method)
		pSelf,
		// used if `other` is passed as self
		pOther
	) };

	// ^^^ this is not a unique_ptr or shared_ptr on purpose, we don't want this class to destruct
	// and we also don't set the pointer itself to nullptr so it's left dangling
	// the class will selfdestruct anyway with `delete this;`

	Result = RValue{ parcast<void*>(pCR) };
}

funcdef(ParCallResult_OnStoreAuthURLResponse) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	
	auto pCR{ new CParCallResultHandler<StoreAuthURLResponse_t>(
		parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)),
		argument[1],
		(argument_count > 2) ? argument[2] : RValue{ },
		pSelf,
		pOther
	) };

	Result = RValue{ parcast<void*>(pCR) };
}

funcdef(ParCallResult_OnMarketEligibilityResponse) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);

	auto pCR{ new CParCallResultHandler<MarketEligibilityResponse_t>(
		parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)),
		argument[1],
		(argument_count > 2) ? argument[2] : RValue{ },
		pSelf,
		pOther
	) };

	Result = RValue{ parcast<void*>(pCR) };
}

funcdef(ParCallResult_OnDurationControl) {
	ensureargc(2);
	ensurekind(0, eRVK_INT64);
	
	auto pCR{ new CParCallResultHandler<DurationControl_t>(
		parcast<unsigned long long>(ParGM()->YYGetInt64(argument, 0)),
		argument[1],
		(argument_count > 2) ? argument[2] : RValue{ },
		pSelf,
		pOther
	) };

	Result = RValue{ parcast<void*>(pCR) };
}

funcdef(ParCallResult_Cancel) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	CParCallResultHandlerBase* pCR{
		parcast<CParCallResultHandlerBase*>(argument[0].ptr)
	};

	if (!pCR) {
		return;
	}

	pCR->CancelThis();
}

funcdef(ParCallResult_IsActive) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	CParCallResultHandlerBase* pCR{
		parcast<CParCallResultHandlerBase*>(argument[0].ptr)
	};

	if (!pCR) {
		return;
	}

	Result = RValue{ pCR->IsThisActive() };
}

funcdef(ParCallResult_SetGameserverFlag) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	CParCallResultHandlerBase* pCR{
		parcast<CParCallResultHandlerBase*>(argument[0].ptr)
	};

	if (!pCR) {
		return;
	}

	pCR->SetThisGameserverFlag();
}

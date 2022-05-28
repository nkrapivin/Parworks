#include "Par.h"
#include "ParGM.h"

funcdef(ParCallResult_OnEncryptedAppTicketResponse) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	EncryptedAppTicketResponse_t* pCallback{
		parcast<EncryptedAppTicketResponse_t*>(
			ParGM()->YYGetPtr(argument, 0)
		)
	};

	if (!pCallback) {
		Result = RValue{ }; // undefined.
		return;
	}

	RValue iCallback{ pCallback->k_iCallback };
	RValue eResult{ pCallback->m_eResult };

	ParGM()->StructCreate(&Result);
	ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&Result, "m_eResult", &eResult);
}

funcdef(ParCallResult_OnStoreAuthURLResponse) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	StoreAuthURLResponse_t* pCallback{
		parcast<StoreAuthURLResponse_t*>(
			ParGM()->YYGetPtr(argument, 0)
		)
	};

	if (!pCallback) {
		Result = RValue{ }; // undefined.
		return;
	}

	RValue iCallback{ pCallback->k_iCallback };

	ParGM()->StructCreate(&Result);
	ParGM()->StructAddRValue(&Result, "k_iCallback", &iCallback);
	ParGM()->StructAddString(&Result, "m_szURL", pCallback->m_szURL);
}

funcdef(ParCallResult_OnMarketEligibilityResponse) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	MarketEligibilityResponse_t* pCallback{
		parcast<MarketEligibilityResponse_t*>(
			ParGM()->YYGetPtr(argument, 0)
		)
	};

	if (!pCallback) {
		Result = RValue{ }; // undefined.
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

funcdef(ParCallResult_OnDurationControl) {
	ensureargc(1);
	ensurekind(0, eRVK_PTR);

	DurationControl_t* pCallback{
		parcast<DurationControl_t*>(
			ParGM()->YYGetPtr(argument, 0)
		)
	};

	if (!pCallback) {
		Result = RValue{ }; // undefined.
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

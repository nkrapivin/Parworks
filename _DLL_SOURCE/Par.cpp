// Par.cpp : Определяет экспортируемые функции для DLL.
//

#include "Par.h"
#include "ParGM.h"
#include <array>

static YYRunnerInterface _YY{ nullptr };
static CParGMCalls* _ParGMCalls{ nullptr };
TYYBuiltin F_ScriptExecute{ nullptr };
YYObjectBase* g_pGlobal{ nullptr };
bool ParInIDE{ false };

const YYRunnerInterface* ParGM() {
	return &_YY;
}

static void Par_OnSteamInputConfigurationLoaded(SteamInputConfigurationLoaded_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res { };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue unAppID{ pParam->m_unAppID };
	RValue ulDeviceHandle{ pParam->m_ulDeviceHandle };
	RValue ulMappingCreator{ pParam->m_ulMappingCreator.ConvertToUint64() };
	RValue unMajorRevision{ pParam->m_unMajorRevision };
	RValue unMinorRevision{ pParam->m_unMinorRevision };
	RValue bUsesSteamInputAPI{ pParam->m_bUsesSteamInputAPI };
	RValue bUsesGamepadAPI{ pParam->m_bUsesGamepadAPI };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_unAppID", &unAppID);
	ParGM()->StructAddRValue(&args[1], "m_ulDeviceHandle", &ulDeviceHandle);
	ParGM()->StructAddRValue(&args[1], "m_ulMappingCreator", &ulMappingCreator);
	ParGM()->StructAddRValue(&args[1], "m_unMajorRevision", &unMajorRevision);
	ParGM()->StructAddRValue(&args[1], "m_unMinorRevision", &unMinorRevision);
	ParGM()->StructAddRValue(&args[1], "m_bUsesSteamInputAPI", &bUsesSteamInputAPI);
	ParGM()->StructAddRValue(&args[1], "m_bUsesGamepadAPI", &bUsesGamepadAPI);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamInputDeviceConnected(SteamInputDeviceConnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue ulConnectedDeviceHandle{ pParam->m_ulConnectedDeviceHandle };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_ulConnectedDeviceHandle", &ulConnectedDeviceHandle);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamInputDeviceDisconnected(SteamInputDeviceDisconnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue ulDisconnectedDeviceHandle{ pParam->m_ulDisconnectedDeviceHandle };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_ulDisconnectedDeviceHandle", &ulDisconnectedDeviceHandle);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnFloatingGamepadTextInputDismissed(FloatingGamepadTextInputDismissed_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnGamepadTextInputDismissed(GamepadTextInputDismissed_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue bSubmitted{ pParam->m_bSubmitted };
	RValue unSubmittedText{ pParam->m_unSubmittedText };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_bSubmitted", &bSubmitted);
	ParGM()->StructAddRValue(&args[1], "m_unSubmittedText", &unSubmittedText);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnAppResumingFromSuspend(AppResumingFromSuspend_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamShutdown(SteamShutdown_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnRemoteStorageLocalFileChange(RemoteStorageLocalFileChange_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamServersConnected(SteamServersConnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamServersDisconnected(SteamServersDisconnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue eResult{ pParam->m_eResult };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_eResult", &eResult);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamServerConnectFailure(SteamServerConnectFailure_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue eResult{ pParam->m_eResult };
	RValue bStillRetrying{ pParam->m_bStillRetrying };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_eResult", &eResult);
	ParGM()->StructAddRValue(&args[1], "m_bStillRetrying", &bStillRetrying);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnSteamAPICallCompleted(SteamAPICallCompleted_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue hAsyncCall{ pParam->m_hAsyncCall };
	RValue _iCallback{ pParam->m_iCallback };
	RValue cubParam{ pParam->m_cubParam };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_hAsyncCall", &hAsyncCall);
	ParGM()->StructAddRValue(&args[1], "m_iCallback", &_iCallback);
	ParGM()->StructAddRValue(&args[1], "m_cubParam", &cubParam);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnLowBatteryPower(LowBatteryPower_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue nMinutesBatteryLeft{ pParam->m_nMinutesBatteryLeft };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_nMinutesBatteryLeft", &nMinutesBatteryLeft);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnIPCountry(IPCountry_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue SteamID{ pParam->m_SteamID.ConvertToUint64() };
	RValue eAuthSessionResponse{ pParam->m_eAuthSessionResponse };
	RValue OwnerSteamID{ pParam->m_OwnerSteamID.ConvertToUint64() };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_SteamID", &SteamID);
	ParGM()->StructAddRValue(&args[1], "m_eAuthSessionResponse", &eAuthSessionResponse);
	ParGM()->StructAddRValue(&args[1], "m_OwnerSteamID", &OwnerSteamID);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnGameWebCallback(GameWebCallback_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddString(&args[1], "m_szURL", pParam->m_szURL);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnGetAuthSessionTicketResponse(GetAuthSessionTicketResponse_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue hAuthTicket{ pParam->m_hAuthTicket };
	RValue eResult{ pParam->m_eResult };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_hAuthTicket", &hAuthTicket);
	ParGM()->StructAddRValue(&args[1], "m_eResult", &eResult);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnLicensesUpdated(LicensesUpdated_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnIPCFailure(IPCFailure_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue eFailureType{ pParam->m_eFailureType };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_eFailureType", &eFailureType);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnMicroTxnAuthorizationResponse(MicroTxnAuthorizationResponse_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue unAppID{ pParam->m_unAppID };
	RValue ulOrderID{ pParam->m_ulOrderID };
	RValue bAuthorized{ pParam->m_bAuthorized };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_unAppID", &unAppID);
	ParGM()->StructAddRValue(&args[1], "m_ulOrderID", &ulOrderID);
	ParGM()->StructAddRValue(&args[1], "m_bAuthorized", &bAuthorized);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

static void Par_OnClientGameServerDeny(ClientGameServerDeny_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	std::array<RValue, 2> args{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue uAppID{ pParam->m_uAppID };
	RValue unGameServerIP{ pParam->m_unGameServerIP };
	RValue usGameServerPort{ pParam->m_usGameServerPort };
	RValue bSecure{ pParam->m_bSecure };
	RValue uReason{ pParam->m_uReason };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_uAppID", &uAppID);
	ParGM()->StructAddRValue(&args[1], "m_unGameServerIP", &unGameServerIP);
	ParGM()->StructAddRValue(&args[1], "m_usGameServerPort", &usGameServerPort);
	ParGM()->StructAddRValue(&args[1], "m_bSecure", &bSecure);
	ParGM()->StructAddRValue(&args[1], "m_uReason", &uReason);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		parcast<int>(args.size()),
		args.data()
	);
}

CParGMCalls::CParGMCalls() {
	m_bIsReady = false;
	// the internal steamworks callback fields have constructors and are auto-initialized.
}

CParGMCalls* ParGMCalls() {
	if (!_ParGMCalls) {
		_ParGMCalls = new CParGMCalls{};
	}

	return _ParGMCalls;
}

void CParGMCalls::SetIsReady(bool bNewIsReady) {
	m_bIsReady = bNewIsReady;
}

void CParGMCalls::OnSteamInputConfigurationLoaded(SteamInputConfigurationLoaded_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamInputConfigurationLoaded(pParam);
}

void CParGMCalls::OnSteamInputDeviceConnected(SteamInputDeviceConnected_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamInputDeviceConnected(pParam);
}

void CParGMCalls::OnSteamInputDeviceDisconnected(SteamInputDeviceDisconnected_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamInputDeviceDisconnected(pParam);
}

void CParGMCalls::OnFloatingGamepadTextInputDismissed(FloatingGamepadTextInputDismissed_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnFloatingGamepadTextInputDismissed(pParam);
}

void CParGMCalls::OnGamepadTextInputDismissed(GamepadTextInputDismissed_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnGamepadTextInputDismissed(pParam);
}

void CParGMCalls::OnAppResumingFromSuspend(AppResumingFromSuspend_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnAppResumingFromSuspend(pParam);
}

void CParGMCalls::OnSteamShutdown(SteamShutdown_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamShutdown(pParam);
}

void CParGMCalls::OnRemoteStorageLocalFileChange(RemoteStorageLocalFileChange_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnRemoteStorageLocalFileChange(pParam);
}

void CParGMCalls::OnSteamServersConnected(SteamServersConnected_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamServersConnected(pParam);
}

void CParGMCalls::OnSteamServersDisconnected(SteamServersDisconnected_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamServersDisconnected(pParam);
}

void CParGMCalls::OnSteamServerConnectFailure(SteamServerConnectFailure_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamServerConnectFailure(pParam);
}

void CParGMCalls::OnSteamAPICallCompleted(SteamAPICallCompleted_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnSteamAPICallCompleted(pParam);
}

void CParGMCalls::OnLowBatteryPower(LowBatteryPower_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnLowBatteryPower(pParam);
}

void CParGMCalls::OnIPCountry(IPCountry_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnIPCountry(pParam);
}

void CParGMCalls::OnValidateAuthTicketResponse(ValidateAuthTicketResponse_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnValidateAuthTicketResponse(pParam);
}

void CParGMCalls::OnGameWebCallback(GameWebCallback_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnGameWebCallback(pParam);
}

void CParGMCalls::OnGetAuthSessionTicketResponse(GetAuthSessionTicketResponse_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnGetAuthSessionTicketResponse(pParam);
}

void CParGMCalls::OnLicensesUpdated(LicensesUpdated_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnLicensesUpdated(pParam);
}

void CParGMCalls::OnIPCFailure(IPCFailure_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnIPCFailure(pParam);
}

void CParGMCalls::OnMicroTxnAuthorizationResponse(MicroTxnAuthorizationResponse_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnMicroTxnAuthorizationResponse(pParam);
}

void CParGMCalls::OnClientGameServerDeny(ClientGameServerDeny_t* pParam) {
	if (!m_bIsReady) {
		return;
	}

	Par_OnClientGameServerDeny(pParam);
}

parex
void YYExtensionInitialise(const struct YYRunnerInterface* _pFunctions, size_t _functions_size) {
	partrace("Welcome! This is Parworks by @nkrapivindev. Built at: " __DATE__ " " __TIME__);

	if (!_pFunctions || _functions_size == 0) {
		partrace("YYRunnerInterface* or size are null. Will crash.");
		return;
	}

	if (_functions_size < sizeof(*_pFunctions)) {
		partrace(
			"YYRunnerInterface size is older than this dll expects, wanted %zu got %zu. Will crash.",
			sizeof(*_pFunctions),
			_functions_size
		);
		return;
	}

	// yay
	_YY = *_pFunctions;
	partrace("YYRunnerInterface size %zu is initialised.", _functions_size);

	// poke ISteamUtils and see if it's there
	if (!SteamUtils()) {
		partrace("Steam doesn't seem to be initialised. The game will crash.");
	}

	if (ParInIDE) {
		partrace("Running in IDE or Debug mode. RestartAppIfNecessary was not called.");
	}
}

funcdef(Par_DummyFunction) {
	// does nothing...
}

funcdef(Par_ScriptCallSetup) {
	ensureargc(2);
	ensurekind(0, eRVK_OBJECT);
	ensurekind(1, eRVK_OBJECT);

	F_ScriptExecute = argument[0].scref->m_callCpp;
	g_pGlobal = argument[1].obj;
	// activate the callback listener thingy
	ParGMCalls()->SetIsReady(true);

	partrace("ScriptCallSetup is ready, script_executeptr=0x%p,cbselfptr=0x%p", F_ScriptExecute, g_pGlobal);
}

funcdef(Par_Shutdown) {
	partrace("Shutting down Steam API...");
	SteamAPI_Shutdown();
}

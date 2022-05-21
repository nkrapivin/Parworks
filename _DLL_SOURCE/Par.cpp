﻿// Par.cpp : Определяет экспортируемые функции для DLL.
//

#include "Par.h"
#include "ParGM.h"

static YYRunnerInterface _YY{ nullptr };
static CParGMCalls* _ParGMCalls{ nullptr };
TYYBuiltin F_ScriptExecute{ nullptr };
YYObjectBase* g_pGlobal{ nullptr };

const YYRunnerInterface* ParGM() {
	return &_YY;
}

static void Par_OnSteamInputConfigurationLoaded(SteamInputConfigurationLoaded_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res { };
	RValue args[2]{ RValue{ ind }, RValue { } };

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
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnSteamInputDeviceConnected(SteamInputDeviceConnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue ulConnectedDeviceHandle{ pParam->m_ulConnectedDeviceHandle };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_ulConnectedDeviceHandle", &ulConnectedDeviceHandle);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnSteamInputDeviceDisconnected(SteamInputDeviceDisconnected_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };
	RValue ulDisconnectedDeviceHandle{ pParam->m_ulDisconnectedDeviceHandle };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);
	ParGM()->StructAddRValue(&args[1], "m_ulDisconnectedDeviceHandle", &ulDisconnectedDeviceHandle);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnFloatingGamepadTextInputDismissed(FloatingGamepadTextInputDismissed_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnGamepadTextInputDismissed(GamepadTextInputDismissed_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

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
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnAppResumingFromSuspend(AppResumingFromSuspend_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnSteamShutdown(SteamShutdown_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

static void Par_OnRemoteStorageLocalFileChange(RemoteStorageLocalFileChange_t* pParam) {
	int ind{ ParGM()->Script_Find_Id(__FUNCTION__) };

	if (ind < 0) {
		return;
	}

	RValue res{ };
	RValue args[2]{ RValue{ ind }, RValue { } };

	RValue iCallback{ pParam->k_iCallback };

	ParGM()->StructCreate(&args[1]);
	ParGM()->StructAddRValue(&args[1], "k_iCallback", &iCallback);

	F_ScriptExecute(
		res,
		parcast<CInstance*>(g_pGlobal),
		parcast<CInstance*>(g_pGlobal),
		sizeof(args) / sizeof(args[0]),
		args
	);
}

CParGMCalls::CParGMCalls() {
	m_bIsReady = false;
	// the internal steamworks callback fields have constructors and are auto-initialized.
}

CParGMCalls* ParGMCalls() {
	if (!_ParGMCalls) {
		_ParGMCalls = new CParGMCalls();
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

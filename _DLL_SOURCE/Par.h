#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS 1
#define parex __declspec(dllexport)
#else
#define parex __attribute__((visibility("default")))
#endif

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <steam_api.h>

// TODO: replace with a more type safe cast?
#define parcast static_cast

#include "ParGM.h"

// stores various ids and keys to call into GML
class CParGMCalls {
	// -- begin -- //

public:

	CParGMCalls();

	bool m_bIsReady;

private:

	STEAM_CALLBACK( CParGMCalls, OnSteamInputConfigurationLoaded,     SteamInputConfigurationLoaded_t     );

	STEAM_CALLBACK( CParGMCalls, OnSteamInputDeviceConnected,         SteamInputDeviceConnected_t         );

	STEAM_CALLBACK( CParGMCalls, OnSteamInputDeviceDisconnected,      SteamInputDeviceDisconnected_t      );

	STEAM_CALLBACK( CParGMCalls, OnFloatingGamepadTextInputDismissed, FloatingGamepadTextInputDismissed_t );

	// -- end   -- //
};

extern CParGMCalls* ParGMCalls();

extern TYYBuiltin F_ScriptExecute;
extern YYObjectBase* g_pGlobal;

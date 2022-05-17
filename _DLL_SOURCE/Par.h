#pragma once

#ifdef _WIN32

#define _CRT_SECURE_NO_WARNINGS 1

#ifdef PAR_EXPORTS
#define parex __declspec(dllexport)
#else
#define parex __declspec(dllimport)
#endif

#else

#define parex __attribute__((visibility("default")))

#endif

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <steam_api.h>

// TODO: replace with a more type safe cast?
#define parcast static_cast
#define cparcast const_cast
#define rparcast reinterpret_cast

#define partrace(...) do { printf("[Par|%s;%d]: ", __FUNCTION__, __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout); } while (false)

// stores various ids and keys to call into GML
class CParGMCalls {
	// -- begin -- //

public:

	CParGMCalls();

	virtual void SetIsReady(bool bNewIsReady);

private:

	bool m_bIsReady;

	STEAM_CALLBACK( CParGMCalls, OnSteamInputConfigurationLoaded,     SteamInputConfigurationLoaded_t     );

	STEAM_CALLBACK( CParGMCalls, OnSteamInputDeviceConnected,         SteamInputDeviceConnected_t         );

	STEAM_CALLBACK( CParGMCalls, OnSteamInputDeviceDisconnected,      SteamInputDeviceDisconnected_t      );

	STEAM_CALLBACK( CParGMCalls, OnFloatingGamepadTextInputDismissed, FloatingGamepadTextInputDismissed_t );

	STEAM_CALLBACK( CParGMCalls, OnGamepadTextInputDismissed,         GamepadTextInputDismissed_t         );

	STEAM_CALLBACK( CParGMCalls, OnAppResumingFromSuspend,            AppResumingFromSuspend_t            );

	STEAM_CALLBACK( CParGMCalls, OnSteamShutdown,                     SteamShutdown_t                     );

	STEAM_CALLBACK( CParGMCalls, OnRemoteStorageLocalFileChange,      RemoteStorageLocalFileChange_t      );

	// -- end   -- //
};

extern CParGMCalls* ParGMCalls();


#include "Par.h"
#include "ParIDECheck.h"
#include <limits>
#include <cstdlib>

#include <cstdio>

// TODO: finish up this code...
#if 0

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMCX
#define NOMINMAX
#include <Windows.h>
// yay windows crap
#else /* !_WIN32 */
#include <fcntl.h>
#include <errno.h>
#endif /* _WIN32 */

static bool IsRunningInsideIDE() {
	// The reason why I don't use std::array<> or std::string here is because it's a 'critical' function
	// inside PreGraphicsInitialisation and I don't want any C++ crap to interfere.
	// and I don't want any exceptions as well lmao.

#ifdef _WIN32
	// WinAPI implementation:
	LPWSTR cmdline{ GetCommandLineW() };
	return cmdline && ((!wcsstr(cmdline, L"-pardisableidemode")) && (wcsstr(cmdline, L"-parforceidemode") || wcsstr(cmdline, L"-game \"")));
#else
#ifdef __linux__
	// Linux implementation:
	char argsbuffer[8192]{ '\0' };
	const size_t argslen{ sizeof(argsbuffer) / sizeof(argsbuffer[0]) };

	int cmdlinefd{ open("/proc/self/cmdline", O_RDONLY) };
	if (cmdlinefd < 0) {
		// ????????????
		return false;
	}

	// -1 to guarantee that the last byte is null...
	read(cmdlinefd, argsbuffer, argslen - 1);
	close(cmdlinefd); cmdlinefd = -1;

	// cmdline is a NULL-separated file, so we have to loop manually
	char* argstart{ &argsbuffer[0] };
	char* argend{ &argsbuffer[argslen] };
	for (char* curstr{ argstart }; curstr != argend; curstr += strlen(curstr)) {
		// should technically never happen...
		if (!*curstr) {
			break;
		}

		// hehe...
		if (strstr(curstr, "-pardisableidemode")) {
			return false;
		}

		//  a manual Par-specific override,        REALLY running through an IDE, -game "/tmp/funny/example/test.win"
		if (strstr(curstr, "-parforceidemode") || strstr(curstr, "-game \"")) {
			return true;
		}
	}
#else /* !__linux__ */
	// macOS implementation:

	return false;
#endif /* __linux__ */
#endif /* _WIN32 */
}

extern "C"
parex
void PreGraphicsInitialisation(const char* argument0) {
	AppId_t myappid{ 0 };
	unsigned long tmp{ 0 };
	pardbgwait();

	// a zero-length or empty string is invalid anyway...
	if (!argument0 || strlen(argument0) == 0) {
		partrace("[!!!! EARLY INIT ERROR !!!!] AppId is not set or empty.");
		exit(0);
		return;
	}

	tmp = strtoul(argument0, nullptr, 10);
	// a 0 AppID is invalid, and I'm pretty sure ULONG_MAX is as well.
	if (tmp == std::numeric_limits<unsigned long>::min()
	||  tmp == std::numeric_limits<unsigned long>::max()) {
		partrace("[!!!! EARLY INIT ERROR !!!!] Invalid AppId is passed to config -> '%s'...?", argument0);
		exit(0);
		return;
	}

	myappid = parcast<AppId_t>(tmp);
	partrace("Using AppId -> '%u'", myappid);

	ParInIDE = IsRunningInsideIDE();
	if (!ParInIDE) {
		partrace("Not running through an Editor.");

		if (SteamAPI_RestartAppIfNecessary(myappid)) {
			partrace("[!!!! EARLY INIT ERROR !!!!] Oh my fur and whiskers, need to quit, exit if you insist, stop even!!");
			exit(0);
			return;
		}
	}

	if (!SteamAPI_Init()) {
		partrace("[!!!! EARLY INIT ERROR !!!!] Unable to initialize Steam, most functions will return `undefined`!");
		// do not exit() here since this may be intentional ... :|
	}
}

#endif

#pragma once

#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef _DEBUG
#define SETUP_CONSOLE(S) \
			AllocConsole(); \
			SetConsoleTitle(S); \
			FILE* pFile; \
			freopen_s(&pFile, "CONIN$", "r", stdin); \
			freopen_s(&pFile, "CONOUT$", "w", stdout); \
			freopen_s(&pFile, "CONOUT$", "w", stderr)
	#ifdef UNICODE
		#define LOG(S) std::wcout << S << std::endl
		#define LOG_INFO(S) std::wcout << "[I] " << S << std::endl
		#define LOG_WARNING(S) std::wcout << "[W] " << S << std::endl
		#define LOG_ERROR(S) std::wcout << "[E] " << S << std::endl
	#else
		#define LOG(S) std::cout << S << std::endl
		#define LOG_INFO(S) std::cout << "[I] " << S << std::endl
		#define LOG_WARNING(S) std::cout << "[W] " << S << std::endl
		#define LOG_ERROR(S) std::cout << "[E] " << S << std::endl
	#endif
#else
	#define LOG(S)
	#define LOG_INFO(S)
	#define LOG_WARNING(S)
	#define LOG_ERROR(S)
	#define SETUP_CONSOLE(S)
#endif

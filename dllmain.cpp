// dllmain.cpp : Defines the entry point for the DLL application.

#include "utility/Log.hpp"
#include <tlhelp32.h>
#include "LoPBars.hpp"

#define PROXY_DLL L"XInput1_3.dll"

static HMODULE gProxyLib = NULL;

extern "C"
{
	DWORD WINAPI XInputGetState(DWORD dwUserIndex, PVOID pState)
	{
		return reinterpret_cast<decltype(XInputGetState)*>(GetProcAddress(gProxyLib, "XInputGetState"))(dwUserIndex, pState);
	}

	DWORD WINAPI XInputSetState(DWORD dwUserIndex, PVOID pVibration)
	{
		return reinterpret_cast<decltype(XInputSetState)*>(GetProcAddress(gProxyLib, "XInputSetState"))(dwUserIndex, pVibration);
	}

	DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, PVOID pCapabilities)
	{
		return reinterpret_cast<decltype(XInputGetCapabilities)*>(GetProcAddress(gProxyLib, "XInputGetCapabilities"))(dwUserIndex, dwFlags, pCapabilities);
	}

	void WINAPI XInputEnable(BOOL enable)
	{
		reinterpret_cast<decltype(XInputEnable)*>(GetProcAddress(gProxyLib, "XInputEnable"))(enable);
	}

	DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, PVOID pDSoundRenderGuid, PVOID pDSoundCaptureGuid)
	{
		return reinterpret_cast<decltype(XInputGetDSoundAudioDeviceGuids)*>(GetProcAddress(gProxyLib, "XInputGetDSoundAudioDeviceGuids"))(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
	}

	DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, PVOID pBatteryInformation)
	{
		return reinterpret_cast<decltype(XInputGetBatteryInformation)*>(GetProcAddress(gProxyLib, "XInputGetBatteryInformation"))(dwUserIndex, devType, pBatteryInformation);
	}

	DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PVOID pKeystroke)
	{
		return reinterpret_cast<decltype(XInputGetKeystroke)*>(GetProcAddress(gProxyLib, "XInputGetKeystroke"))(dwUserIndex, dwReserved, pKeystroke);
	}

	// XInput 1.3 undocumented functions
	DWORD WINAPI XInputGetStateEx(DWORD dwUserIndex, PVOID pState)
	{
		//return reinterpret_cast<decltype(XInputGetStateEx)*>(GetProcAddress(gProxyLib, "XInputGetStateEx"))(dwUserIndex, pState);
		return reinterpret_cast<decltype(XInputGetStateEx)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(100)))(dwUserIndex, pState);
	}

	DWORD WINAPI XInputWaitForGuideButton(DWORD dwUserIndex, DWORD dwFlag, PVOID ptr)
	{
		//return reinterpret_cast<decltype(XInputWaitForGuideButton)*>(GetProcAddress(gProxyLib, "XInputWaitForGuideButton"))(dwUserIndex, dwFlag, ptr);
		return reinterpret_cast<decltype(XInputWaitForGuideButton)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(101)))(dwUserIndex, dwFlag, ptr);
	}

	DWORD WINAPI XInputCancelGuideButtonWait(DWORD dwUserIndex)
	{
		//return reinterpret_cast<decltype(XInputCancelGuideButtonWait)*>(GetProcAddress(gProxyLib, "XInputCancelGuideButtonWait"))(dwUserIndex);
		return reinterpret_cast<decltype(XInputCancelGuideButtonWait)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(102)))(dwUserIndex);
	}

	DWORD WINAPI XInputPowerOffController(DWORD dwUserIndex)
	{
		//return reinterpret_cast<decltype(XInputPowerOffController)*>(GetProcAddress(gProxyLib, "XInputPowerOffController"))(dwUserIndex);
		return reinterpret_cast<decltype(XInputPowerOffController)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(103)))(dwUserIndex);
	}

	// XInput 1.4 functions
	//DWORD WINAPI XInputGetAudioDeviceIds(DWORD dwUserIndex, PVOID pRenderDeviceId, PVOID pRenderCount, PVOID pCaptureDeviceId, PVOID pCaptureCount)
	//{
	//    return reinterpret_cast<decltype(XInputGetAudioDeviceIds)*>(GetProcAddress(gProxyLib, "XInputGetAudioDeviceIds"))(dwUserIndex, pRenderDeviceId, pRenderCount, pCaptureDeviceId, pCaptureCount);
	//}

	//DWORD WINAPI XInputGetBaseBusInformation(DWORD dwUserIndex, PVOID pBusInfo)
	//{
	//    return reinterpret_cast<decltype(XInputGetBaseBusInformation)*>(GetProcAddress(gProxyLib, "XInputGetBaseBusInformation"))(dwUserIndex, pBusInfo);
	//    return reinterpret_cast<decltype(XInputGetBaseBusInformation)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(104)))(dwUserIndex, pBusInfo);
	//}

	//DWORD WINAPI XInputGetCapabilitiesEx(DWORD dwUnk, DWORD dwUserIndex, DWORD dwFlags, PVOID pCapabilities)
	//{
	//    return reinterpret_cast<decltype(XInputGetCapabilitiesEx)*>(GetProcAddress(gProxyLib, "XInputGetCapabilitiesEx"))(dwUnk, dwUserIndex, dwFlags, pCapabilities);
	//    return reinterpret_cast<decltype(XInputGetCapabilitiesEx)*>(GetProcAddress(gProxyLib, reinterpret_cast<LPCSTR>(108)))(dwUnk, dwUserIndex, dwFlags, pCapabilities);
	//}
}

static DWORD WINAPI InitializeProxy(LPVOID lpThreadParameter)
{
	SETUP_CONSOLE(L"LoP Bars");

	LOG_INFO("LoP Bars DLL loaded!");
	LOG_INFO("Loading target library " << PROXY_DLL << "...");

	WCHAR sysDir[MAX_PATH] = {};
	if (GetSystemDirectoryW(sysDir, MAX_PATH) == 0)
	{
		LOG_ERROR("Failed to retrieve system directory");
		return 1;
	}

	const std::wstring wsSysDir = std::wstring{ sysDir } + L"\\" + PROXY_DLL;
	gProxyLib = LoadLibraryW(wsSysDir.c_str());
	if (gProxyLib == NULL)
	{
		const std::wstring wsErrorMsg = L"Failed to find \"" + wsSysDir;
		LOG_ERROR(wsErrorMsg);
		MessageBox(0, wsErrorMsg.c_str(), L"LoP Bars", MB_OK | MB_ICONERROR);
		return 1;
	}

	LOG_INFO("Library " << PROXY_DLL << " loaded successfully!");

#ifdef _DEBUG
	MessageBox(0, L"Waiting for debugger...", L"LoP Bars", MB_OK | MB_ICONINFORMATION);
#endif

	try
	{
		LoPBars::GetInstance();
	}
	catch (std::exception& e)
	{
		MessageBoxA(0, e.what(), "LoP Bars", MB_OK | MB_ICONERROR);
		return 2;
	}

	return 0;
}

static void Cleanup()
{
	LOG_INFO("Detaching DLL...");
	FreeLibrary(gProxyLib);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// DLL loaded via proxy if (GetCurrentThreadId() == GetMainThreadID())
		// else DLL loaded manually
		CreateThread(NULL, 0, InitializeProxy, NULL, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Cleanup();
		break;
	}

	return TRUE;
}

// Modified from https://github.com/praydog/REFramework source code

#include <unordered_map>
#include <vector>
#include <mutex>
#include "utility/Log.hpp"
#include "utility/Thread.hpp"
#include "WindowsMessageHook.hpp"

static std::recursive_mutex gProcMutex;

LRESULT WINAPI WindowProc(HWND wnd, UINT dwMessage, WPARAM wParam, LPARAM lParam)
{
	std::scoped_lock _{ gProcMutex };

	auto &msgHook = WindowsMessageHook::GetInstance();

	// Call our onMessage callback.
	auto& fnOnMessage = msgHook.GetOnMessage();

	if (fnOnMessage)
	{
		// If it returns false we don't call the original window procedure.
		if (!fnOnMessage(wnd, dwMessage, wParam, lParam))
		{
			return DefWindowProc(wnd, dwMessage, wParam, lParam);
		}
	}

	// Call the original message procedure.
	return CallWindowProc(msgHook.GetOriginal(), wnd, dwMessage, wParam, lParam);
}

WindowsMessageHook::WindowsMessageHook() : hwnd(nullptr), fnOriginalProc(nullptr), fnOnMessage(nullptr)
{

}

WindowsMessageHook::~WindowsMessageHook()
{
	std::scoped_lock _{ gProcMutex };

	LOG_INFO("Destroying WindowsMessageHook");

	utility::ThreadSuspender suspender;

	Unhook();
}

bool WindowsMessageHook::IsHookIntact()
{
	if (!hwnd)
	{
		return false;
	}

	return GetWindowLongPtr(hwnd, GWLP_WNDPROC) == (LONG_PTR)&WindowProc;
}

bool WindowsMessageHook::Hook(HWND hwnd)
{
	this->hwnd = hwnd;

	LOG_INFO("Hooking Windows message handler...");

	utility::ThreadSuspender suspender;

	// Save the original window procedure.
	fnOriginalProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);

	// Set it to our "hook" procedure.
	return SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&WindowProc) != 0;
}

bool WindowsMessageHook::Unhook()
{
	// Don't attempt to restore invalid original window procedures.
	if (fnOriginalProc == nullptr || hwnd == nullptr)
	{
		return false;
	}

	LOG_INFO("Unhooking Windows message handler...");

	// Restore the original window procedure.
	auto fnCurrentProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);

	// lets not try to restore the original window procedure if it's not ours.
	if (fnCurrentProc == &WindowProc)
	{
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)fnOriginalProc);
	}

	// Invalidate this message hook.
	hwnd = nullptr;
	fnOriginalProc = nullptr;

	return true;
}

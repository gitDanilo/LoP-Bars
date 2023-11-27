// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <functional>
#include <Windows.h>

#define LB_TOGGLE_CURSOR WM_APP + 1

class WindowsMessageHook
{
public:
	typedef std::function<bool(HWND, UINT, WPARAM, LPARAM)> OnMessageFn;

	static WindowsMessageHook& GetInstance()
	{
		static WindowsMessageHook instance;
		return instance;
	}

	WindowsMessageHook(const WindowsMessageHook& other) = delete;
	WindowsMessageHook(WindowsMessageHook&& other) = delete;

	WindowsMessageHook& operator=(const WindowsMessageHook& other) = delete;
	WindowsMessageHook& operator=(const WindowsMessageHook&& other) = delete;

	virtual ~WindowsMessageHook();

	bool IsHookIntact();
	bool Hook(HWND hwnd);
	bool Unhook();

	inline void SetOnMessage(OnMessageFn onMsgFn)
	{
		this->fnOnMessage = onMsgFn;
	}

	inline OnMessageFn& GetOnMessage()
	{
		return this->fnOnMessage;
	}

	inline auto IsValid() const
	{
		return fnOriginalProc != nullptr;
	}

	inline auto GetOriginal() const
	{
		return fnOriginalProc;
	}

	inline void WindowToggleCursor(bool show)
	{
		::PostMessage(hwnd, LB_TOGGLE_CURSOR, show, 1);
	}
private:
	WindowsMessageHook();

	OnMessageFn fnOnMessage;
	HWND hwnd;
	WNDPROC fnOriginalProc;
};

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class ImGuiWindow
{
public:
	virtual ~ImGuiWindow() {};
	virtual bool OnInitialize() = 0;
	virtual void OnReset() = 0;
	virtual void OnDraw() = 0;
	virtual bool OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) = 0;
};

#pragma once

#include "ImGuiWindow.hpp"
#include "ImGui.h"
#include <chrono>

using namespace std::literals;

#define SPLASH_FIRST_TIME_DURATION 20s
#define SPLASH_DURATION 5s

class Splash : public ImGuiWindow
{
public:
	Splash();
	~Splash() override;
	bool OnInitialize() override;
	void OnReset() override;
	void OnDraw() override;
	bool OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) override;
private:
	bool bIsExpired;
	bool bIsFirstTime;
	std::chrono::seconds splashDuration;
	std::chrono::steady_clock::time_point startTime;
	ImGuiWindowFlags windowFlags;

	void ShowWelcomeWindow();
	void ShowSplashWindow();
};

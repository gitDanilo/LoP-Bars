#include "Splash.hpp"
#include "ImGui.h"
#include "ConfigManager.hpp"

Splash::Splash() : bIsExpired(false), bIsFirstTime(true), startTime(), splashDuration()
{
	windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
}

Splash::~Splash()
{

}

bool Splash::OnInitialize()
{
	bIsFirstTime = ConfigManager::GetInstance().Get<int>("IsFirstTime").value_or(1);
	splashDuration = bIsFirstTime ? SPLASH_FIRST_TIME_DURATION : SPLASH_DURATION;
	return true;
}

void Splash::OnReset()
{

}

void Splash::OnDraw()
{
	if (bIsExpired)
		return;

	if (startTime <= std::chrono::high_resolution_clock::time_point(0s))
		startTime = std::chrono::high_resolution_clock::now();
	else if (std::chrono::high_resolution_clock::now() - startTime > splashDuration)
	{
		bIsExpired = true;
		bIsFirstTime = false;
		ConfigManager::GetInstance().Set<int>("IsFirstTime", 0);
		return;
	}

	auto viewport = ImGui::GetMainViewport();
	constexpr auto PAD = 10.0f;

	ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x + PAD, viewport->WorkPos.y + PAD), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.5f);

	if (bIsFirstTime)
		ShowWelcomeWindow();
	else
		ShowSplashWindow();
}

bool Splash::OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return true;
}

void Splash::ShowWelcomeWindow()
{
	ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
	if (ImGui::Begin("Welcome", nullptr, windowFlags))
	{
		ImGui::SeparatorText("Welcome to LoP Bars");
		ImGui::Text("How to use:");
		ImGui::Text("Lock onto an enemy to activate the overlay.");
		ImGui::NewLine();
		ImGui::Text("Bindings:");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "HOME");
		ImGui::SameLine();
		ImGui::Text("Toggle overlay ON/OFF");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "PG_UP");
		ImGui::SameLine();
		ImGui::Text("Reset window position");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "PG_DOWN");
		ImGui::SameLine();
		ImGui::Text("Toggle window drag ON/OFF");
		ImGui::NewLine();
		ImGui::Text("Mod created by: Nashnaiderman");
	}
	ImGui::End();
}

void Splash::ShowSplashWindow()
{
	ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f));
	if (ImGui::Begin("Splash", nullptr, windowFlags))
	{
		ImGui::Text("LoP Bars is initializing...");
		ImGui::NewLine();
		ImGui::Text("Mod created by: Nashnaiderman");
	}
	ImGui::End();
}

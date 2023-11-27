#pragma once

#include "ImGuiWindow.hpp"

class EntityBars : public ImGuiWindow
{
public:
	EntityBars();
	~EntityBars() override;
	// Inherited via ImGuiWindow
	void OnDraw() override;
	bool OnInitialize() override;
	void OnReset() override;
	bool OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) override;
private:
	bool bShowDemo;
};

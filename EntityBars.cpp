#include "EntityBars.hpp"
#include "imgui.h"
#include "utility/Log.hpp"

EntityBars::EntityBars()
{
	bShowDemo = false;
}

EntityBars::~EntityBars()
{

}

void EntityBars::OnDraw()
{
	ImGui::GetIO().MouseDrawCursor = bShowDemo;
	if (bShowDemo)
	{
		ImGui::ShowDemoWindow();
	}
}

bool EntityBars::OnInitialize()
{
	return false;
}

void EntityBars::OnReset()
{
}

bool EntityBars::OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (iMsg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		bShowDemo = !bShowDemo;
	}
	return !bShowDemo;
}

#pragma once

#include <mutex>
#include "imgui.h"
#include "ImGuiWindow.hpp"

enum WINDOW_POSITION : int
{
	TOP_LEFT = 0,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_RIGHT,
	BOTTOM_RIGHT,
	BOTTOM_CENTER,
	BOTTOM_LEFT,
	CENTER_LEFT,
	CUSTOM
};

struct INPUT_DATA
{
	bool bShowWindow;
	bool bEnableDrag;
	WINDOW_POSITION iPosition;
};

struct MUTEX_INPUT_DATA : INPUT_DATA
{
	std::mutex mutex;

	inline void GetData(INPUT_DATA& inputData)
	{
		std::scoped_lock _{ mutex };
		memcpy(&inputData, this, sizeof(INPUT_DATA));
	}
};

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
	MUTEX_INPUT_DATA inputData;
	void GetWindowPos(WINDOW_POSITION iPosition, ImVec2& windowPos, ImVec2& windowPosPivot, const float PAD = 10.0f);
};

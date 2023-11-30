#pragma once

#include <mutex>
#include <thread>
#include <chrono>
#include "imgui.h"
#include "ImGuiWindow.hpp"
#include "utility/FunctionHook.hpp"

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

struct ABNORMAL_STAT_LIST
{
	char* pList;
	int iNewSlot;

	void GetElementalBuildup(float& fire, float& eletric, float& acid);
};

struct ENTITY_PTRS
{
	char* pBase;
	char* pStatList;
	ABNORMAL_STAT_LIST abnormalStatList;
};

static const short SET_LOCKON_FN_SIG[] = {
	0x7F, 0x2C,                       // jg 14DB60EAB
	0x48, 0x89, 0xC1,                 // mov rcx,rax
	0x48, 0x8B, 0x42, 0x30,           // mov rax,[rdx+30]
	0x4C, 0x39, 0x04, 0xC8,           // cmp [rax+rcx*8],r8
	0x75, 0x1F,                       // jne 14DB60EAB
	0x48, 0x89, 0xBB, -1, -1, -1, -1, // mov [rbx+00000098],rdi
	0x66, 0x8B, 0x3D, -1, -1, -1, -1, // mov di,[157F4D673]
	0x21, 0x3D                        // and [15742208D],edi
};

static const size_t SET_LOCKON_FN_SIG_OFFSET = 0x2D;

typedef int(__stdcall* GetMaxDurability)(void* pWeapon);

class EntityBars : public ImGuiWindow
{
public:
	EntityBars();
	~EntityBars() override;
	void OnDraw() override;
	bool OnInitialize() override;
	void OnReset() override;
	bool OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) override;
	static void __stdcall SetLockOnSystemData(void* unknown1, void* pLockOnSystemData, void* unknown2);
private:
	bool bIsInitialized;
	MUTEX_INPUT_DATA inputData;
	std::unique_ptr<FunctionHook> pSetLockOnHook;
	char* pLockOnSystemData;
	ENTITY_PTRS lockedEntity;
	void GetWindowPos(WINDOW_POSITION iPosition, ImVec2& windowPos, ImVec2& windowPosPivot, const float PAD = 10.0f);
};

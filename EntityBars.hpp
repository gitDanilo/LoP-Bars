#pragma once

#define NOMINMAX

#include <mutex>
#include <thread>
#include <chrono>
#include "imgui.h"
#include "ImGuiWindow.hpp"
#include "utility/FunctionHook.hpp"

using namespace std::string_view_literals;

struct WND_CONTEXT
{
	bool bShowWindow;
	bool bEnableDrag;
	bool bCustomPosition;
};

struct MUTEX_WND_CONTEXT : WND_CONTEXT
{
	std::mutex mutex;

	inline void GetData(WND_CONTEXT& context)
	{
		std::scoped_lock _{ mutex };
		memcpy(&context, this, sizeof(WND_CONTEXT));
	}
};

// --------------------------------ELEMENTAL BUILDUP---------------------------------------
enum E_TYPE : unsigned char
{
	UNKNOWN = 0,
	FIRE,
	ELETRIC,
	ACID,
	COUNT,
};

// Elements Max resist offset from StatList
static const unsigned int E_RESIST_OFFSET[] =
{
	0xFFFFFFFF, // Unknown
	0x16BC, // Fire
	0x16EC, // Eletric
	0x171C, // Acid
};

static const ImVec4 E_COLOR[] =
{
	ImVec4(0.0f, 0.0f, 0.0f, 0.0f), // Unknown
	ImVec4(0.8f, 0.4f, 0.0f, 1.0f), // Fire
	ImVec4(0.0f, 0.3f, 0.8f, 1.0f), // Eletric
	ImVec4(0.0f, 0.5f, 0.4f, 1.0f), // Acid
};

static const std::string_view E_NAME[] =
{
	"Unknown"sv,
	"Fire"sv,
	"Eletric"sv,
	"Acid"sv,
};

struct E_BAR
{
	float fValues[2];
	std::string sBarText;
};

static E_BAR E_BAR_LIST[E_TYPE::COUNT] = { 0 };
// ----------------------------------------------------------------------------------------

enum ENTITY_FACTION : unsigned char
{
	F_NONE = 0,
	F_PLAYER,
	F_MONSTER,
	F_ALLENEMY,
	F_NEUTRAL,

	F_PLAYER_HITENABLE,
	F_MONSTER_PUPPET,
	F_MONSTER_CARCASS,
	F_MONSTER_REBORNER,
	F_MONSTER_STALKER,
	F_ENEMY_TOONLYPLAYER,
	F_MONSTER_CARCASSNPUPPET,

	F_MAX,
	F_DEFAULT,
};

enum ENTITY_STATS : unsigned char
{
	S_NONE = 0,

	S_HEALTH_POINT_CURRENT = 1,
	S_STAMINA_POINT_CURRENT = 2,
	S_TOUGH_POINT_CURRENT = 9,
	S_GROGGY_POINT_CURRENT = 48,

	S_HEALTH_POINT_MAX = 71,
	S_STAMINA_POINT_MAX = 72,
	S_TOUGH_POINT_MAX = 76,
	S_GROGGY_POINT_MAX = 78,

	S_MAX = 190,
	S_DEFAULT = 191,
};

struct LIST_DATA
{
	char* pList;
	int iSize;
};

struct ENTITY_PTRS
{
	unsigned char bFaction;
	char* pBase;
	LIST_DATA statList;
	LIST_DATA buffList;
	LIST_DATA abnormalStatList;
	LIST_DATA weaponList;
};

static const short SET_LOCKON_FN_SIG[] =
{
	0x48, 0x89, 0x5C, 0x24, 0x08,
	0x57,
	0x48, 0x83, 0xEC, 0x20,
	0x48, 0x89, 0xD7,
	0x48, 0x89, 0xCB,
	0x48, 0x85, 0xD2,
	0x0F, 0x84, -1, -1, -1, -1,
	0xE8, -1, -1, -1, -1,
	0x48, 0x8B, 0x57, 0x10,
	0x4C, 0x8D, 0x40, 0x30,
	0x48, 0x63, 0x40, 0x38,
	0x3B, 0x42, 0x38,
	0x7F, -1,
	0x48, 0x89, 0xC1,
	0x48, 0x8B, 0x42, 0x30,
	0x4C, 0x39, 0x04, 0xC8,
	0x75, -1,
	0x48, 0x89, 0xBB, 0x98, 0x00, 0x00, 0x00,
	0x66, 0x8B ,0x3D,
};

static const size_t SET_LOCKON_FN_SIG_OFFSET = 0x0;

static const short GET_MAX_DURABILITY_FN_SIG[] =
{
	0x40, 0x57,
	0x48, 0x83, 0xEC, 0x20,
	0x48, 0x8B, 0xB9, 0x38, 0x03, 0x00, 0x00,
	0x48, 0x85, 0xFF,
	0x0F, 0x84, -1, -1, -1, -1,
	0x48, 0x89, 0x5C, 0x24, 0x30,
	0x48, 0x63, 0x5F, 0x50,
	0xE8, -1, -1, -1, -1,
	0x8B, 0x97, 0xD0, 0x00, 0x00, 0x00,
	0x48, 0x89, 0xC1,
	0xE8, -1, -1, -1, -1,
	0x48, 0x85, 0xC0,
	0x74,
};

static const size_t GET_MAX_DURABILITY_OFFSET = 0x0;

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
	MUTEX_WND_CONTEXT context;

	std::unique_ptr<FunctionHook> pSetLockOnHook;
	char* pLockOnSystemData;
	ENTITY_PTRS target;
	GetMaxDurability fnGetMaxDurability;

	inline void ShowBasicStats(int iValues[], float fValues[], const ImVec2& progressBarSize);
	inline void ShowElementalBuildup(const ImVec2& progressBarSize);
	inline void ShowWeaponsDurability(int iValues[], const ImVec2& progressBarSize);
};

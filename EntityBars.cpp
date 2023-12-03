#include "EntityBars.hpp"
#include "utility/Module.hpp"
#include "utility/Memory.hpp"
#include "utility/Log.hpp"
#include "ConfigManager.hpp"
#include <format>
#include <limits>

static EntityBars* gEntityBars = nullptr;

EntityBars::EntityBars() : context(), bIsInitialized(false), pLockOnSystemData(nullptr), target(), fnGetMaxDurability(nullptr)
{
	gEntityBars = this;
	context.bShowWindow = true;
}

EntityBars::~EntityBars()
{
	if (pSetLockOnHook != nullptr)
	{
		pSetLockOnHook->Remove();
	}

	gEntityBars = nullptr;
}

void EntityBars::SetLockOnSystemData(void* unknown1, void* pLockOnSystemData, void* unknown2)
{
	LOG_INFO("SetLockOnSystemData called with: " << std::hex << unknown1 << ", " << pLockOnSystemData << ", " << unknown2);

	auto fnSetLockOn = gEntityBars->pSetLockOnHook->GetOriginal<decltype(EntityBars::SetLockOnSystemData)>();

	gEntityBars->pLockOnSystemData = (char*)pLockOnSystemData;

	fnSetLockOn(unknown1, pLockOnSystemData, unknown2);
}

bool EntityBars::OnInitialize()
{
	LOG_INFO("Initializing EntityBars...");

	context.bCustomPosition = ConfigManager::GetInstance().Get<int>("IsCustomPosition").value_or(0);

	HMODULE hExec = utility::GetExecutable();
	if (hExec == NULL)
	{
		LOG_ERROR("Failed to get executable address");
		return false;
	}

	std::optional<size_t> sizeExec = utility::GetModuleSize(hExec);
	if (!sizeExec.has_value())
	{
		LOG_ERROR("Failed to get executable size");
		return false;
	}

	auto pFunction = utility::PatternScan(SET_LOCKON_FN_SIG, sizeof(SET_LOCKON_FN_SIG), hExec, sizeExec.value_or(0));
	if (pFunction == nullptr)
	{
		LOG_ERROR("Failed to find SetLockOn function signature");
		return false;
	}

	//if (utility::PatternScan(SET_LOCKON_FN_SIGNATURE, sizeof(SET_LOCKON_FN_SIGNATURE), pFunction + 1, sizeExec.value_or(0)) != nullptr)
	//{
	//	LOG_ERROR("Failed to find the unique function signature of SetLockOn");
	//	return false;
	//}

	pFunction -= SET_LOCKON_FN_SIG_OFFSET;

	pSetLockOnHook = std::make_unique<FunctionHook>(pFunction, &EntityBars::SetLockOnSystemData);
	if (!pSetLockOnHook->Create())
	{
		return false;
	}

	pFunction = utility::PatternScan(GET_MAX_DURABILITY_FN_SIG, sizeof(GET_MAX_DURABILITY_FN_SIG), hExec, sizeExec.value_or(0));
	if (pFunction == nullptr)
	{
		return false;
	}

	fnGetMaxDurability = (GetMaxDurability)pFunction;

	bIsInitialized = true;

	//pThreadUpdateEntity = std::make_unique<std::jthread>(std::bind_front(&EntityBars::UpdateEntityData, this));

	LOG_INFO("EntityBars initialized!");

	return true;
}

void EntityBars::OnReset()
{
	if (!bIsInitialized)
		return;

	std::scoped_lock _{ context.mutex };
	context.bEnableDrag = false;
}

void EntityBars::ShowBasicStats(int iValues[], float fValues[], const ImVec2& progressBarSize)
{
	ImGui::SeparatorText("Stats");

	// Health
	iValues[0] = *(int*)(target.pStatList + 0xC);
	iValues[1] = *(int*)(target.pStatList + 0xD2C);
	std::string sText = std::format("Health ({}/{})", iValues[0], iValues[1]);
	ImGui::ProgressBar((float)iValues[0] / (float)iValues[1], progressBarSize, sText.c_str(), ImVec4(0.4f, 0.0f, 0.0f, 1.0f));

	// Stamina
	iValues[0] = *(int*)(target.pStatList + 0x3C);
	iValues[1] = *(int*)(target.pStatList + 0xD5C);
	sText = std::format("Stamina ({}/{})", iValues[0], iValues[1]);
	ImGui::ProgressBar((float)iValues[0] / (float)iValues[1], progressBarSize, sText.c_str(), ImVec4(0.0f, 0.4f, 0.0f, 1.0f));

	// Tough
	iValues[0] = *(int*)(target.pStatList + 0x18C);
	iValues[1] = *(int*)(target.pStatList + 0xE1C);
	sText = std::format("Posture ({}/{})", iValues[0], iValues[1]);
	ImGui::ProgressBar((float)iValues[0] / (float)iValues[1], progressBarSize, sText.c_str(), ImVec4(0.5f, 0.0f, 0.5f, 1.0f));

	// Stagger
	iValues[0] = *(int*)(target.pStatList + 0x8DC); // Stagger point
	iValues[1] = *(int*)(target.pStatList + 0xE7C); // Max stagger point
	fValues[1] = *(float*)(target.pBase + 0xF60); // Stagger max duration
	if (iValues[0] == 0 && fValues[1] > 1.0f)
	{
		fValues[0] = *(float*)(target.pBase + 0xF68); // Stagger retain/duration
		sText = std::vformat("Stagger {:.2f}s"sv, std::make_format_args(fValues[0]));
		ImGui::ProgressBar(fValues[0] / fValues[1], progressBarSize, sText.c_str(), ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
	}
	else if (iValues[1] > 0)
	{
		sText = std::format("Stagger ({}/{})", iValues[0], iValues[1]);
		ImGui::ProgressBar((float)iValues[0] / (float)iValues[1], progressBarSize, sText.c_str(), ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
	}
}

void EntityBars::ShowElementalBuildup(const ImVec2& progressBarSize)
{
	size_t end = (target.abnormalStatList.iSize * 0x10);
	uintptr_t itemAddr;
	char e;
	bool bIsDebuffActive;

	memset(E_BAR_LIST, 0, sizeof(E_BAR) * E_TYPE::COUNT);

	for (size_t i = 0; i < end; i += 0x10)
	{
		itemAddr = *(uintptr_t*)(target.abnormalStatList.pList + i);

		e = *(char*)(*(uintptr_t*)(itemAddr + 0x8) + 0x84); // Element type

		if (e < E_TYPE::FIRE || e > E_TYPE::COUNT - 1) // Skip unsupported types
			continue;

		E_BAR_LIST[e].fValues[0] = *(float*)(itemAddr + 0x258); // Current buildup
		E_BAR_LIST[e].fValues[1] = (float)*(int*)(target.pStatList + E_RESIST_OFFSET[e]); // Max buildup
		bIsDebuffActive = (E_BAR_LIST[e].fValues[0] == E_BAR_LIST[e].fValues[1]); // Check if debuff is active

		// Get Retain values if debuff is active
		if (bIsDebuffActive)
		{
			E_BAR_LIST[e].fValues[0] = *(int*)(itemAddr + 0x74) / 1000.0f; // Buildup retain in seconds
			E_BAR_LIST[e].fValues[1] = *(int*)(itemAddr + 0x78) / 1000.0f; // Buildup max retain in seconds
			if (E_BAR_LIST[e].fValues[0] < 0.0f)
				E_BAR_LIST[e].fValues[0] = 0.0f;
		}

		// Set the progress bar text
		E_BAR_LIST[e].sBarText = bIsDebuffActive ?
			std::format("{} {:.2f}s"sv, E_NAME[e], E_BAR_LIST[e].fValues[0]) :
			std::format("{} ({}/{})"sv, E_NAME[e], (int)E_BAR_LIST[e].fValues[0], (int)E_BAR_LIST[e].fValues[1]);
	}

	ImGui::SeparatorText("Buildup");

	for (char i = E_TYPE::FIRE; i < E_TYPE::COUNT; ++i)
	{
		if (E_BAR_LIST[i].fValues[1] <= 0.0f)
		{
			E_BAR_LIST[i].fValues[1] = (float)*(int*)(target.pStatList + E_RESIST_OFFSET[i]); // Max buildup
			E_BAR_LIST[i].sBarText = std::format("{} ({}/{})"sv, E_NAME[i], 0.0f, (int)E_BAR_LIST[i].fValues[1]);
		}
		ImGui::ProgressBar(E_BAR_LIST[i].fValues[0] / E_BAR_LIST[i].fValues[1], progressBarSize, E_BAR_LIST[i].sBarText.c_str(), E_COLOR[i]);
	}

}

void EntityBars::ShowWeaponsDurability(int iValues[], const ImVec2& progressBarSize)
{
	char* pWeapon;
	bool bShowHeader = true;

	for (int i = 0; i < target.weaponList.iSize; ++i)
	{
		pWeapon = (char*)*(uintptr_t*)(target.weaponList.pList + (i * sizeof(void*)));
		iValues[0] = *(int*)(pWeapon + 0x308);

		if (iValues[0] < 0)
			continue;

		if (bShowHeader)
		{
			bShowHeader = false;
			ImGui::SeparatorText("Weapons");
		}

		iValues[1] = fnGetMaxDurability(pWeapon);
		std::string sText = std::format("Durability ({}/{})", iValues[0], iValues[1]);
		ImGui::ProgressBar((float)iValues[0] / (float)iValues[1], progressBarSize, sText.c_str(), ImVec4(0.9f, 0.7f, 0.0f, 1.0f));
	}
}

void EntityBars::OnDraw()
{
	if (!bIsInitialized)
		return;

	static WND_CONTEXT tmpContext;
	context.GetData(tmpContext);

	if (!tmpContext.bShowWindow || pLockOnSystemData == nullptr)
		return;

	target.pBase = (char*)*(uintptr_t*)(pLockOnSystemData + 0x200);
	if (target.pBase == nullptr)
		return;

	// Check if entity has any basic stats. If don't, then skip
	uintptr_t ptr = *(uintptr_t*)(target.pBase + 0x848);
	if (utility::IsBadReadPtr((void*)ptr))
		return;

	target.pStatList = (char*)*(uintptr_t*)(*(uintptr_t*)(ptr + 0xE0) + 0x28);

	// Check if entity has any abnormal stats
	ptr = *(uintptr_t*)(target.pBase + 0x850);
	if (utility::IsBadReadPtr((void*)ptr))
		target.abnormalStatList.iSize = -1;
	else
		target.abnormalStatList = *(LIST_DATA*)(ptr + 0xD0);

	// Check if weapon list is valid
	target.weaponList = *(LIST_DATA*)(target.pBase + 0xE0);
	if (utility::IsBadReadPtr(target.weaponList.pList))
		target.weaponList.iSize = -1;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	if (!tmpContext.bEnableDrag)
		windowFlags = windowFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
	else
		ImGui::SetNextWindowFocus();

	auto& io = ImGui::GetIO();

	io.MouseDrawCursor = tmpContext.bEnableDrag;

	if (!tmpContext.bCustomPosition)
	{
		ImVec2 windowPos, windowPosPivot;
		auto viewport = ImGui::GetMainViewport();
		windowPos.x = viewport->WorkPos.x + viewport->WorkSize.x - 10.0f;
		windowPos.y = viewport->GetCenter().y;
		windowPosPivot.x = 1.0f;
		windowPosPivot.y = 0.5f;
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
	}

	static ImVec2 progressBarSize = ImVec2(-1.0f, ImGui::GetFontSize() + 7.0f);

	ImGui::SetNextWindowSize(ImVec2(220.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.5f);

	if (ImGui::Begin("Entity Bars", nullptr, windowFlags))
	{
		int iValues[2];
		float fValues[2];

		ShowBasicStats(iValues, fValues, progressBarSize);

		if (target.abnormalStatList.iSize > -1)
			ShowElementalBuildup(progressBarSize);

		if (target.weaponList.iSize > 0)
			ShowWeaponsDurability(iValues, progressBarSize);
	}
	ImGui::End();
}

bool EntityBars::OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (!bIsInitialized)
		return true;

	switch (iMsg)
	{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			if (context.bEnableDrag)
				return false;
			break;
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_HOME: // Toggle overlay
				{
					std::scoped_lock _{ context.mutex };
					context.bShowWindow = !context.bShowWindow;
				}
				return false;
				case VK_PRIOR: // Reset window position
					if (context.bShowWindow)
					{
						std::scoped_lock _{ context.mutex };
						context.bEnableDrag = false;
						context.bCustomPosition = false;
						ConfigManager::GetInstance().Set<int>("IsCustomPosition", 0);
					}
					return false;
				case VK_NEXT: // Toggle window drag and resize 
					if (context.bShowWindow)
					{
						std::scoped_lock _{ context.mutex };
						context.bEnableDrag = !context.bEnableDrag;
						context.bCustomPosition = true;
						if (!context.bEnableDrag)
							ConfigManager::GetInstance().Set<int>("IsCustomPosition", 1);
					}
					return false;
			}
		}
		break;
	}
	return true;
}

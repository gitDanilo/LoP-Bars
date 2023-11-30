#include "EntityBars.hpp"
#include "utility/Module.hpp"
#include "utility/Memory.hpp"
#include "utility/Log.hpp"
#include <format>

static EntityBars* gEntityBars = nullptr;

void ABNORMAL_STAT_LIST::GetElementalBuildup(float& fire, float& eletric, float& acid)
{
	fire = 0.0f;
	eletric = 0.0f;
	acid = 0.0f;

	if (iNewSlot < 3)
		return;

	size_t last = 0x20 + ((iNewSlot - 2) * 0x10);
	char iClass;

	for (size_t i = 0x20; i < last; i += 0x10)
	{
		iClass = *(char*)(*(uintptr_t*)(*(uintptr_t*)(pList + i) + 0x8) + 0x84);
		switch (iClass)
		{
		case 0x1:
			fire = trunc(*(float*)(*(uintptr_t*)(pList + i) + 0x258));
			continue;
		case 0x2:
			eletric = trunc(*(float*)(*(uintptr_t*)(pList + i) + 0x258));
			continue;
		case 0x3:
			acid = trunc(*(float*)(*(uintptr_t*)(pList + i) + 0x258));
			continue;
		default:
			continue;
		}
	}
}

EntityBars::EntityBars() : inputData(), bIsInitialized(false), pLockOnSystemData(nullptr), lockedEntity(), fnGetMaxDurability(nullptr)
{
	gEntityBars = this;
	inputData.bShowWindow = true;
	inputData.iPosition = WINDOW_POSITION::CENTER_RIGHT;
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

void EntityBars::GetWindowPos(WINDOW_POSITION iPosition, ImVec2& windowPos, ImVec2& windowPosPivot, const float PAD)
{
	auto viewport = ImGui::GetMainViewport();
	switch (iPosition)
	{
	case WINDOW_POSITION::TOP_LEFT:
		windowPos.x = viewport->WorkPos.x + PAD;
		windowPos.y = viewport->WorkPos.y + PAD;
		windowPosPivot.x = 0.0f;
		windowPosPivot.y = 0.0f;
		break;
	case WINDOW_POSITION::CENTER_LEFT:
		windowPos.x = viewport->WorkPos.x + PAD;
		windowPos.y = viewport->GetCenter().y;
		windowPosPivot.x = 0.0f;
		windowPosPivot.y = 0.5f;
		break;
	case WINDOW_POSITION::BOTTOM_LEFT:
		windowPos.x = viewport->WorkPos.x + PAD;
		windowPos.y = viewport->WorkPos.y + viewport->WorkSize.y - PAD;
		windowPosPivot.x = 0.0f;
		windowPosPivot.y = 1.0f;
		break;

	case WINDOW_POSITION::TOP_CENTER:
		windowPos.x = viewport->GetCenter().x;
		windowPos.y = viewport->WorkPos.y + PAD;
		windowPosPivot.x = 0.5f;
		windowPosPivot.y = 0.0f;
		break;
	case WINDOW_POSITION::BOTTOM_CENTER:
		windowPos.x = viewport->GetCenter().x;
		windowPos.y = viewport->WorkPos.y + viewport->WorkSize.y - PAD;
		windowPosPivot.x = 0.5f;
		windowPosPivot.y = 1.0f;
		break;

	case WINDOW_POSITION::TOP_RIGHT:
		windowPos.x = viewport->WorkPos.x + viewport->WorkSize.x - PAD;
		windowPos.y = viewport->WorkPos.y + PAD;
		windowPosPivot.x = 1.0f;
		windowPosPivot.y = 0.0f;
		break;
	case WINDOW_POSITION::CENTER_RIGHT:
		windowPos.x = viewport->WorkPos.x + viewport->WorkSize.x - PAD;
		windowPos.y = viewport->GetCenter().y;
		windowPosPivot.x = 1.0f;
		windowPosPivot.y = 0.5f;
		break;
	case WINDOW_POSITION::BOTTOM_RIGHT:
		windowPos.x = viewport->WorkPos.x + viewport->WorkSize.x - PAD;
		windowPos.y = viewport->WorkPos.y + viewport->WorkSize.y - PAD;
		windowPosPivot.x = 1.0f;
		windowPosPivot.y = 1.0f;
		break;
	}
}

void EntityBars::OnDraw()
{
	if (!bIsInitialized)
		return;

	static INPUT_DATA tmpInputData = { 0 };
	inputData.GetData(tmpInputData);

	if (!tmpInputData.bShowWindow || pLockOnSystemData == nullptr)
		return;

	lockedEntity.pBase = (char*)*(uintptr_t*)(pLockOnSystemData + 0x200);
	if (lockedEntity.pBase == nullptr)
		return;

	lockedEntity.pStatList = (char*)*(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(lockedEntity.pBase + 0x848) + 0xE0) + 0x28);
	lockedEntity.abnormalStatList = *(ABNORMAL_STAT_LIST*)(*(uintptr_t*)(lockedEntity.pBase + 0x850) + 0xD0);

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav;

	if (!tmpInputData.bEnableDrag)
		windowFlags = windowFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
	else
		ImGui::SetNextWindowFocus();

	auto& io = ImGui::GetIO();

	io.MouseDrawCursor = tmpInputData.bEnableDrag;

	constexpr auto PAD = 10.0f;
	const ImVec2 progressBarSize = ImVec2(-1.0f, ImGui::GetFontSize() + 5.0f);

	if (tmpInputData.iPosition != WINDOW_POSITION::CUSTOM)
	{
		ImVec2 windowPos(0, 0), windowPosPivot(0, 0);
		GetWindowPos(tmpInputData.iPosition, windowPos, windowPosPivot, 10.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
	}

	ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.45f);
	if (ImGui::Begin("Entity Bars", nullptr, windowFlags))
	{
		ImGui::SeparatorText("Stats");

		// Health
		int iValue = *(int*)(lockedEntity.pStatList + 0xC);
		int iMaxValue = *(int*)(lockedEntity.pStatList + 0xD2C);
		std::string sText = std::format("Health ({}/{})", iValue, iMaxValue);
		ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.35f, 0.0f, 0.0f, 0.85f));

		// Stamina
		iValue = *(int*)(lockedEntity.pStatList + 0x3C);
		iMaxValue = *(int*)(lockedEntity.pStatList + 0xD5C);
		sText = std::format("Stamina ({}/{})", iValue, iMaxValue);
		ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.2f, 0.45f, 0.0f, 0.85f));

		// Tough
		iValue = *(int*)(lockedEntity.pStatList + 0x18C);
		iMaxValue = *(int*)(lockedEntity.pStatList + 0xE1C);
		sText = std::format("Posture ({}/{})", iValue, iMaxValue);
		ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.45f, 0.0f, 0.5f, 0.85f));

		float fValue = 100.0f;
		float fMaxValue = 100.0f;

		// Stagger
		iValue = *(int*)(lockedEntity.pStatList + 0x8DC);
		if (iValue == 0)
		{
			// Stagger elapsed time
			//fValue = *(float*)(lockedEntity.pBase + 0xF64); // Stagger elapsed time
			fValue = *(float*)(lockedEntity.pBase + 0xF68); // Stagger duration time
			fMaxValue = *(float*)(lockedEntity.pBase + 0xF60); // Stagger duration

			sText = std::format("Stagger duration {}s", (int)fValue);
			ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.9f, 0.7f, 0.0f, 0.85f));
		}
		else
		{
			iMaxValue = *(int*)(lockedEntity.pStatList + 0xE7C);
			sText = std::format("Stagger ({}/{})", iValue, iMaxValue);
			ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.9f, 0.7f, 0.0f, 0.85f));
		}

		ImGui::SeparatorText("Buildup");

		float fEletric, fAcid;
		lockedEntity.abnormalStatList.GetElementalBuildup(fValue, fEletric, fAcid);

		fMaxValue = (float)*(int*)(lockedEntity.pStatList + 0x16BC);
		sText = std::format("Fire ({}/{})", fValue, fMaxValue);
		ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.8f, 0.4f, 0.0f, 0.85f));

		fMaxValue = (float)*(int*)(lockedEntity.pStatList + 0x16EC);
		sText = std::format("Eletric ({}/{})", fEletric, fMaxValue);
		ImGui::ProgressBar(fEletric / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.0f, 0.25f, 0.75f, 0.85f));

		fMaxValue = (float)*(int*)(lockedEntity.pStatList + 0x171C);
		sText = std::format("Acid ({}/{})", fAcid, fMaxValue);
		ImGui::ProgressBar(fAcid / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.2f, 0.45f, 0.0f, 0.85f));

		lockedEntity.weaponList = *(WEAPON_LIST*)(lockedEntity.pBase + 0xE0);
		if (lockedEntity.weaponList.iWeaponCount > 0)
		{
			ImGui::SeparatorText("Weapons");
			char* pWeapon;
			for (int i = 0; i < lockedEntity.weaponList.iWeaponCount; ++i)
			{
				pWeapon = (char*)*(uintptr_t*)(lockedEntity.weaponList.pList + (i * sizeof(void*)));
				iValue = *(int*)(pWeapon + 0x308);
				iMaxValue = fnGetMaxDurability(pWeapon);
				sText = std::format("Durability ({}/{})", i + 1, iValue, iMaxValue);
				ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.2f, 0.45f, 0.0f, 0.85f));
			}
		}
	}
	ImGui::End();
}

bool EntityBars::OnInitialize()
{
	LOG_INFO("Initializing EntityBars...");

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

	bIsInitialized = true;

	//pThreadUpdateEntity = std::make_unique<std::jthread>(std::bind_front(&EntityBars::UpdateEntityData, this));

	LOG_INFO("EntityBars initialized!");

	return true;
}

void EntityBars::OnReset()
{
	if (!bIsInitialized)
		return;

	std::scoped_lock _{ inputData.mutex };
	inputData.bEnableDrag = false;
	inputData.iPosition = WINDOW_POSITION::CENTER_RIGHT;
}

bool EntityBars::OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (!bIsInitialized)
		return true;

	static bool isKeyboardInput = false;

	if (iMsg == WM_KEYDOWN)
	{
		isKeyboardInput = true;

		switch (wParam)
		{
		case VK_HOME:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bShowWindow = !inputData.bShowWindow;
		}
		break;
		case VK_END:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = !inputData.bEnableDrag;
			if (inputData.bEnableDrag)
				inputData.iPosition = WINDOW_POSITION::CUSTOM;
		}
		break;
		case VK_PRIOR:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = false;
			inputData.iPosition = WINDOW_POSITION((inputData.iPosition + 1) % WINDOW_POSITION::CUSTOM);
		}
		break;
		case VK_NEXT:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = false;
			inputData.iPosition = WINDOW_POSITION(inputData.iPosition == 0 ? WINDOW_POSITION::CUSTOM - 1 : inputData.iPosition - 1);
		}
		break;
		}
	}

	return isKeyboardInput || !inputData.bEnableDrag;
}

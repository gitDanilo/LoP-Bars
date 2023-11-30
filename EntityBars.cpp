#include "EntityBars.hpp"
#include "utility/Module.hpp"
#include "utility/Memory.hpp"
#include "utility/Log.hpp"
#include <format>

static EntityBars* gEntityBars = nullptr;

EntityBars::EntityBars() : inputData(), bIsInitialized(false), pLockOnSystemData(nullptr), lockedEntity()
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
	lockedEntity.pAbnormalStatsList = (char*)*(uintptr_t*)(*(uintptr_t*)(lockedEntity.pBase + 0x850) + 0xD0);

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
		ImGui::SeparatorText("Basic stats");

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
			fValue = *(float*)(lockedEntity.pBase + 0xF68); // Stagger retain time
			fMaxValue = *(float*)(lockedEntity.pBase + 0xF60); // Stagger duration

			sText = std::format("Stagger retain {0:.2f}s", (int)fValue);
			ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.9f, 0.7f, 0.0f, 0.85f));
		}
		else
		{
			iMaxValue = *(int*)(lockedEntity.pStatList + 0xE7C);
			sText = std::format("Stagger ({}/{})", iValue, iMaxValue);
			ImGui::ProgressBar((float)iValue / (float)iMaxValue, progressBarSize, sText.c_str(), ImVec4(0.9f, 0.7f, 0.0f, 0.85f));
		}

		ImGui::SeparatorText("Elemental buildup");

		fValue = 100.0f;

		fMaxValue = *(int*)(lockedEntity.pStatList + 0x16BC);
		sText = std::format("Fire ({}/{})", fValue, fMaxValue);
		ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.8f, 0.4f, 0.0f, 0.85f));

		fMaxValue = *(int*)(lockedEntity.pStatList + 0x16EC);
		sText = std::format("Acid ({}/{})", fValue, fMaxValue);
		ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.2f, 0.45f, 0.0f, 0.85f));

		fMaxValue = *(int*)(lockedEntity.pStatList + 0x16BC);
		sText = std::format("Eletric ({}/{})", fValue, fMaxValue);
		ImGui::ProgressBar(fValue / fMaxValue, progressBarSize, sText.c_str(), ImVec4(0.0f, 0.25f, 0.75f, 0.85f));

		ImGui::SeparatorText("Timers");

		// Combat
		fValue = *(float*)(lockedEntity.pBase + 0x1040);
		sText = std::format("Combat: {0:.2f}s", fValue);
		ImGui::Text(sText.c_str());
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

	auto fnSetLockOn = utility::PatternScan(SET_LOCKON_FN_SIG, sizeof(SET_LOCKON_FN_SIG), hExec, sizeExec.value_or(0));
	if (fnSetLockOn == nullptr)
	{
		LOG_ERROR("Failed to find SetLockOn function signature");
		return false;
	}

	//if (utility::PatternScan(SET_LOCKON_FN_SIGNATURE, sizeof(SET_LOCKON_FN_SIGNATURE), fnSetLockOn + 1, sizeExec.value_or(0)) != nullptr)
	//{
	//	LOG_ERROR("Failed to find the unique function signature of SetLockOn");
	//	return false;
	//}

	fnSetLockOn -= SET_LOCKON_FN_SIG_OFFSET;

	pSetLockOnHook = std::make_unique<FunctionHook>(fnSetLockOn, &EntityBars::SetLockOnSystemData);
	if (!pSetLockOnHook->Create())
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

	if (iMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_HOME:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bShowWindow = !inputData.bShowWindow;
		}
		return false;
		case VK_END:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = !inputData.bEnableDrag;
			if (inputData.bEnableDrag)
				inputData.iPosition = WINDOW_POSITION::CUSTOM;
		}
		return false;
		case VK_PRIOR:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = false;
			inputData.iPosition = WINDOW_POSITION((inputData.iPosition + 1) % WINDOW_POSITION::CUSTOM);
		}
		return false;
		case VK_NEXT:
		{
			std::scoped_lock _{ inputData.mutex };
			inputData.bEnableDrag = false;
			inputData.iPosition = WINDOW_POSITION(inputData.iPosition == 0 ? WINDOW_POSITION::CUSTOM - 1 : inputData.iPosition - 1);
		}
		return false;
		}
	}

	return !inputData.bEnableDrag;
}

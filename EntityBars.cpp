#include "EntityBars.hpp"
#include "utility/Module.hpp"
#include "utility/Memory.hpp"
#include "utility/Log.hpp"
#include <format>

static EntityBars* gEntityBars = nullptr;

using namespace std::chrono_literals;

EntityBars::EntityBars() : inputData(), lockedEntity(), bIsInitialized(false), pLockOn(nullptr)
{
	gEntityBars = this;
	inputData.bShowWindow = true;
	inputData.iPosition = WINDOW_POSITION::CENTER_RIGHT;
	lockedEntity.bIsActive = false;
}

EntityBars::~EntityBars()
{
	if (pSetLockOnHook != nullptr)
	{
		pSetLockOnHook->Remove();
	}

	if (pThreadUpdateEntity != nullptr)
	{
		pThreadUpdateEntity->request_stop();
		pThreadUpdateEntity.reset();
	}

	gEntityBars = nullptr;
}

void EntityBars::SetLockOn(void* unknown1, void* pLockOn, void* unknown2)
{
	LOG_INFO("SetLockOn called with: " << std::hex << unknown1 << ", " << pLockOn << ", " << unknown2);

	auto fnSetLockOn = gEntityBars->pSetLockOnHook->GetOriginal<decltype(EntityBars::SetLockOn)>();

	gEntityBars->pLockOn = (char*)pLockOn;

	fnSetLockOn(unknown1, pLockOn, unknown2);
}

#define POOLING_INTERVAL 200ms

void EntityBars::UpdateEntityData(std::stop_token stopToken)
{
	LOP_ENTITY tmpEntity = { };
	void* pEntityBase = nullptr;
	void* pLastEntityBase = nullptr;
	void* pTmp = nullptr;
	bool bKeepMaxValues = false;

	int* test = nullptr;

	do
	{
		if (pLockOn == nullptr)
		{
			std::this_thread::sleep_for(POOLING_INTERVAL);
			continue;
		}

		pEntityBase = (void*)*utility::GoodPtrOrNull(pLockOn + 0x200);
		pLastEntityBase = utility::IsBadReadPtr(pLastEntityBase) ? nullptr : pLastEntityBase;

		if (pEntityBase == nullptr && pLastEntityBase == nullptr)
		{
			lockedEntity.bIsActive = false;
			std::this_thread::sleep_for(POOLING_INTERVAL);
			continue;
		}

		pEntityBase = pEntityBase == nullptr ? pLastEntityBase : pEntityBase;
		bKeepMaxValues = pEntityBase == pLastEntityBase;

		test = (int*)utility::ReadMultiLvlPtr(pEntityBase, { 0x848, 0xE0, 0x28, 0xC });
		//test = *(int*)(*(int64_t*)(*(int64_t*)((*(int64_t*)(pEntityBase + 0x848)) + 0xE0) + 0x28) + 0xC);
		LOG_INFO("Health: " << std::dec << (test != nullptr ? *test : -1));

		pLastEntityBase = pEntityBase;
		std::this_thread::sleep_for(POOLING_INTERVAL);
	} while (!stopToken.stop_requested());

	LOG_INFO("Thread UpdateEntityData is stopping...");
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

	if (!tmpInputData.bShowWindow || pLockOn == nullptr)
		return;

	char* pEntityBase = (char*)*(uintptr_t*)(pLockOn + 0x200);
	if (pEntityBase == nullptr)
		return;

	auto& io = ImGui::GetIO();

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoNav;

	if (!tmpInputData.bEnableDrag)
		windowFlags = windowFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
	else
		ImGui::SetNextWindowFocus();

	io.MouseDrawCursor = tmpInputData.bEnableDrag;

	const auto PAD = 10.0f;
	ImVec2 windowPos(0, 0), windowPosPivot(0, 0);
	const ImVec2 progressBarSize = ImVec2(-1.0f, ImGui::GetFontSize() + 5.0f);

	if (tmpInputData.iPosition != WINDOW_POSITION::CUSTOM)
	{
		GetWindowPos(tmpInputData.iPosition, windowPos, windowPosPivot, 10.0f);
		ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
	}
	ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.45f);
	if (ImGui::Begin("Entity Bars", nullptr, windowFlags))
	{
		ImGui::SeparatorText("Basic stats");

		int test = *(int*)(*(uintptr_t*)(*(uintptr_t*)((*(uintptr_t*)(pEntityBase + 0x848)) + 0xE0) + 0x28) + 0xC);
		int test2 = *(int*)(*(uintptr_t*)(*(uintptr_t*)((*(uintptr_t*)(pEntityBase + 0x848)) + 0xE0) + 0x28) + 0xD2C);
		std::string sHealth = std::format("Health ({}/{})", test, test2);
		ImGui::ProgressBar((float)test / (float)test2, progressBarSize, sHealth.c_str(), ImVec4(0.35f, 0.0f, 0.0f, 0.85f));

		int progress = ((int)io.MousePos.y % 100) + 1;
		std::string sStamina = std::format("Stamina ({}/100)", progress);
		ImGui::ProgressBar(progress / 100.0f, progressBarSize, sStamina.c_str(), ImVec4(0.2f, 0.45f, 0.0f, 0.85f));
		ImGui::ProgressBar(0.9f, progressBarSize, "Stagger (90/100)", ImVec4(0.9f, 0.7f, 0.0f, 0.85f));

		ImGui::SeparatorText("Elemental buildup");
		ImGui::ProgressBar(0.3f, progressBarSize, "Fire (30/100)", ImVec4(0.8f, 0.4f, 0.0f, 0.85f));
		ImGui::ProgressBar(0.5f, progressBarSize, "Acid (50/100)", ImVec4(0.45f, 0.735f, 0.045f, 0.85f));
		ImGui::ProgressBar(0.9f, progressBarSize, "Eletric (90/100)", ImVec4(0.0f, 0.25f, 0.75f, 0.85f));

		//ImGui::SeparatorText("Weapons health");
		//ImGui::ProgressBar(0.3f, progressBarSize, "Weapon 1 (30/100)");
		//ImGui::ProgressBar(0.5f, progressBarSize, "Weapon 2 (50/100)");

		ImGui::SeparatorText("Timers");
		ImGui::Text("Combat: 10s");
		ImGui::ProgressBar(1.0f, progressBarSize, "Stagger 12s", ImVec4(0.45f, 0.0f, 0.5f, 0.85f));
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

	pSetLockOnHook = std::make_unique<FunctionHook>(fnSetLockOn, &EntityBars::SetLockOn);
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

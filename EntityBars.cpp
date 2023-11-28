#include "EntityBars.hpp"
#include "utility/Module.hpp"
#include "utility/Memory.hpp"
#include "utility/Log.hpp"
#include <format>

static EntityBars* gEntityBars = nullptr;

EntityBars::EntityBars() : inputData()
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

void EntityBars::SetLockOn(void* unknown1, void* pLockOn, void* unknown2)
{
	auto fnSetLockOn = gEntityBars->pSetLockOnHook->GetOriginal<decltype(EntityBars::SetLockOn)>();

	LOG_INFO("LockOnObj addr: " << std::hex << pLockOn);


	fnSetLockOn(unknown1, pLockOn, unknown2);
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
	static INPUT_DATA tmpInputData = { 0 };
	inputData.GetData(tmpInputData);

	if (tmpInputData.bShowWindow)
	{
		auto& style = ImGui::GetStyle();
		style.WindowRounding = 4.0f;
		style.ChildRounding = 2.0f;
		style.PopupRounding = 2.0f;
		style.FrameRounding = 2.0f;
		style.ScrollbarRounding = 2.0f;
		style.SelectableTextAlign = ImVec2(0.5f, 0.5f);
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.SeparatorTextAlign = ImVec2(0.5f, 0.5f);

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_FrameBg] = ImVec4(0.255f, 0.255f, 0.255f, 0.8f);

		auto& io = ImGui::GetIO();

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoNav;
		if (!tmpInputData.bEnableDrag)
			windowFlags = windowFlags | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove;

		io.MouseDrawCursor = tmpInputData.bEnableDrag;

		const auto PAD = 10.0f;
		ImVec2 windowPos(0, 0), windowPosPivot(0, 0);
		const ImVec2 progressBarSize = ImVec2(-1.0f, 18.0f);

		if (tmpInputData.iPosition != WINDOW_POSITION::CUSTOM)
		{
			GetWindowPos(tmpInputData.iPosition, windowPos, windowPosPivot, 10.0f);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
		}

		//ImGui::SetNextWindowSize(ImVec2(180.0f * io.FontGlobalScale, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.45f);
		if (ImGui::Begin("EntityBars", nullptr, windowFlags))
		{
			ImGui::SeparatorText("Basic stats");
			int progress = ((int)io.MousePos.x % 100) + 1;
			std::string sHealth = std::format("Health ({}/100)", progress);
			ImGui::ProgressBar(progress / 100.0f, progressBarSize, sHealth.c_str(), ImVec4(0.35f, 0.0f, 0.0f, 0.85f));
			progress = ((int)io.MousePos.y % 100) + 1;
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

	auto fnSetLockOn = utility::PatternScan(SET_LOCKON_FN_SIGNATURE, sizeof(SET_LOCKON_FN_SIGNATURE), (char*)hExec, sizeExec.value_or(0));
	if (fnSetLockOn == nullptr)
	{
		LOG_ERROR("Failed to find SetLockOn function signature");
		return false;
	}

	if (utility::PatternScan(SET_LOCKON_FN_SIGNATURE, sizeof(SET_LOCKON_FN_SIGNATURE), fnSetLockOn + 1, sizeExec.value_or(0)) != nullptr)
	{
		LOG_ERROR("Failed to find the unique function signature of SetLockOn");
		return false;
	}

	fnSetLockOn -= SET_LOCKON_FN_SIGNATURE_OFFSET;
	
	pSetLockOnHook = std::make_unique<FunctionHook>(fnSetLockOn, &EntityBars::SetLockOn);
	if (!pSetLockOnHook->Create())
	{
		return false;
	}

	return true;
}

void EntityBars::OnReset()
{
	std::scoped_lock _{ inputData.mutex };
	inputData.bEnableDrag = false;
	inputData.iPosition = WINDOW_POSITION::CENTER_RIGHT;
}

bool EntityBars::OnMessage(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
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

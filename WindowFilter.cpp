// Modified from https://github.com/praydog/REFramework source code

#include "WindowFilter.hpp"

// To prevent usage of statics (TLS breaks the present thread...?)
std::unique_ptr<WindowFilter> gWindowFilter = nullptr;

WindowFilter& WindowFilter::GetInstance()
{
	if (gWindowFilter == nullptr)
	{
		gWindowFilter = std::make_unique<WindowFilter>();
	}

	return *gWindowFilter;
}

WindowFilter::WindowFilter()
{
	// We create a job thread because GetWindowTextA can actually deadlock inside
	// the present thread...
	jobThread = std::make_unique<std::jthread>([this](std::stop_token s)
		{
			while (!s.stop_requested())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				lastJobTick = std::chrono::steady_clock::now();

				if (windowJobs.empty())
				{
					return;
				}

				std::scoped_lock _{ mutex };

				for (const auto hwnd : windowJobs)
				{
					if (IsFilteredNoCache(hwnd))
					{
						FilterWindow(hwnd);
					}
				}

				windowJobs.clear();
			}
		});
}

WindowFilter::~WindowFilter()
{
	jobThread->request_stop();
	jobThread->join();
}

bool WindowFilter::IsFiltered(HWND hwnd)
{
	if (hwnd == nullptr)
	{
		return true;
	}

	std::scoped_lock _{ mutex };

	if (filteredWindows.find(hwnd) != filteredWindows.end())
	{
		return true;
	}

	// If there is a job for this window, filter it until the job is done
	if (windowJobs.find(hwnd) != windowJobs.end())
	{
		// If the thread is dead for some reason, do not filter it.
		return std::chrono::steady_clock::now() - lastJobTick <= std::chrono::seconds{ 2 };
	}

	// if we havent even seen this window yet, add it to the job queue
	// and return true;
	if (seenWindows.find(hwnd) == seenWindows.end())
	{
		seenWindows.insert(hwnd);
		windowJobs.insert(hwnd);
		return true;
	}

	return false;
}

bool WindowFilter::IsFilteredNoCache(HWND hwnd)
{
	char sWindowName[256] = { 0 };
	GetWindowTextA(hwnd, sWindowName, sizeof(sWindowName));

	const auto sv = std::string_view(sWindowName);

	if (sv.find("UE4SS") != std::string_view::npos)
	{
		return true;
	}

	if (sv.find("PimaxXR") != std::string_view::npos)
	{
		return true;
	}

	// TODO: more problematic windows
	return false;
}

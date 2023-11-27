// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <Windows.h>

#include <string_view>
#include <unordered_set>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

class WindowFilter
{
public:
	static WindowFilter& GetInstance();
	WindowFilter();
	virtual ~WindowFilter();
	bool IsFiltered(HWND hwnd);
	void FilterWindow(HWND hwnd)
	{
		std::scoped_lock _{ mutex };
		filteredWindows.insert(hwnd);
	}
private:
	bool IsFilteredNoCache(HWND hwnd);

	std::recursive_mutex mutex;
	std::unordered_set<HWND> windowJobs;
	std::unique_ptr<std::jthread> jobThread;

	std::unordered_set<HWND> seenWindows;
	std::unordered_set<HWND> filteredWindows;
	std::chrono::time_point<std::chrono::steady_clock> lastJobTick;
};

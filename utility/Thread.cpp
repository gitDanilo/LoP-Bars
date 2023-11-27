// Modified from https://github.com/praydog/REFramework source code

#include <mutex>
#include <Windows.h>
#include <TlHelp32.h>
#include "Log.hpp"
#include "Thread.hpp"

static std::mutex gSuspendMutex{};

namespace utility
{
	ThreadSuspender::ThreadSuspender() : suspendedThreads()
	{
		gSuspendMutex.lock();
		SuspendAll();
	}

	ThreadSuspender::~ThreadSuspender()
	{
		if (!suspendedThreads.empty())
			ResumeAll();
		gSuspendMutex.unlock();
	}

	void ThreadSuspender::SuspendAll()
	{
		if (!suspendedThreads.empty())
		{
			LOG_WARNING("Threads already suspended!");
			return;
		}

		LOG_INFO("Suspending all threads...");

		suspendedThreads.clear();

		const DWORD processID = GetCurrentProcessId();
		const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processID);

		if (hSnapshot == INVALID_HANDLE_VALUE)
		{
			LOG_ERROR("Thread suspender failed to create snapshot");
			return;
		}

		THREADENTRY32 entry = { 0 };
		entry.dwSize = sizeof(THREADENTRY32);

		if (!Thread32First(hSnapshot, &entry))
		{
			CloseHandle(hSnapshot);
			return;
		}

		const DWORD currentThreadID = GetCurrentThreadId();
		HANDLE hThread;

		do
		{
			if (entry.th32OwnerProcessID == processID && entry.th32ThreadID != currentThreadID)
			{
				hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, entry.th32ThreadID);
				if (hThread != nullptr)
				{
					SuspendThread(hThread);
					suspendedThreads.push_back(entry.th32ThreadID);
					CloseHandle(hThread);
				}
			}
		} while (Thread32Next(hSnapshot, &entry));

		CloseHandle(hSnapshot);
	}

	void ThreadSuspender::ResumeAll()
	{
		LOG_INFO("Resuming all threads...");

		HANDLE hThread;
		for (const auto threadID : suspendedThreads)
		{
			hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadID);
			if (hThread != nullptr)
			{
				ResumeThread(hThread);
				CloseHandle(hThread);
			}
		}
		suspendedThreads.clear();
	}
}
// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <memory>
#include <vector>

namespace utility
{
	class ThreadSuspender
	{
	public:
		ThreadSuspender();
		virtual ~ThreadSuspender();
		void SuspendAll();
		void ResumeAll();
	private:
		std::vector<DWORD> suspendedThreads;
	};
}

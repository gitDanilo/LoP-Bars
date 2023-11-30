#include "Memory.hpp"
#include <vector>
#include <Windows.h>

namespace utility
{
	inline bool CompareByteArray(const short* aobPattern, const char* aobMemory, size_t size)
	{
		for (auto i = 0; i < size; ++i)
		{
			if (aobPattern[i] != -1 && (char)aobPattern[i] != aobMemory[i])
			{
				return false;
			}
		}
		return true;
	}

	char* PatternScan(const short* aobPattern, size_t patternSize, void* pStartAddress, size_t memorySize)
	{
		size_t patternCount = patternSize / sizeof(short);
		char* pFinalBlock = (char*)pStartAddress + memorySize - patternCount;

		for (auto i = (char*)pStartAddress; i <= pFinalBlock; ++i)
		{
			if (::IsBadReadPtr(i, patternCount) != 0)
			{
				i += patternCount - 1;
				continue;
			}

			if (CompareByteArray(aobPattern, i, patternCount))
			{
				return i;
			}
		}

		return nullptr;
	}

	bool IsBadReadPtr(void* ptr)
	{
		MEMORY_BASIC_INFORMATION mbi;

		if (!::VirtualQuery(ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
			return true;

		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
			return true;

		constexpr DWORD dwMask = (
			PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
			PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY
			);

		return !(mbi.Protect & dwMask);
	}

	inline uintptr_t* GoodPtrOrNull(void* ptr)
	{
		MEMORY_BASIC_INFORMATION mbi;

		if (!::VirtualQuery(ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)))
			return nullptr;

		if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))
			return nullptr;

		constexpr DWORD dwMask = (
			PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
			PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY
			);

		if (!(mbi.Protect & dwMask))
			return nullptr;

		return (uintptr_t*)ptr;
	}

	void* ReadMultiLvlPtr(void* ptr, const std::vector<size_t>& offsetList)
	{
		uintptr_t* pFinal = GoodPtrOrNull(ptr);

		size_t i, last = offsetList.size() - 1;

		for (i = 0; i < offsetList.size() && pFinal != nullptr; ++i)
		{
			pFinal = (uintptr_t*)((char*)pFinal + offsetList[i]);

			if (i == last)
				break;

			pFinal = GoodPtrOrNull(pFinal);
			if (pFinal == nullptr)
				return nullptr;

			pFinal = (uintptr_t*)*pFinal;
		}

		return GoodPtrOrNull(pFinal);
	}
}

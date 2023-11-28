#include "Memory.hpp"
#include <Windows.h>

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

namespace utility
{
	char* PatternScan(const short* aobPattern, size_t patternSize, char* pStartAddress, size_t memorySize)
	{
		size_t patternCount = patternSize / sizeof(short);
		char* pFinalBlock = pStartAddress + memorySize - patternCount;

		for (auto i = pStartAddress; i <= pFinalBlock; ++i)
		{
			if (IsBadReadPtr(i, patternCount) != 0)
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
}

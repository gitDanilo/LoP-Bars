#pragma once

#include <vector>

namespace utility
{
	bool CompareByteArray(const short* aobPattern, const char* aobMemory, size_t size);
	char* PatternScan(const short* aobPattern, size_t patternSize, void* pStartAddress, size_t memorySize);
	bool IsBadReadPtr(void* ptr);
	uintptr_t* GoodPtrOrNull(void* ptr);
	void* ReadMultiLvlPtr(void* ptr, const std::vector<size_t>& offsetList);
}

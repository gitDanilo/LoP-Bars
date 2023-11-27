// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <cstdint>
#include <vector>
#include <Windows.h>
#include "Address.hpp"

class VtableHook
{
public:
	VtableHook();
	VtableHook(Address pTarget);
	VtableHook(const VtableHook& other) = delete;
	VtableHook(VtableHook&& other);

	virtual ~VtableHook();

	bool Create(Address pTarget);
	bool Recreate();
	bool Remove();

	bool HookMethod(uint32_t index, Address pMethod);
	auto GetInstance() { return pVtable; }

	// Access to original methods.
	Address GetMethod(uint32_t index)
	{
		if (index < sizeVtable && pOldVtable && pNewVtable)
		{
			return pOldVtable.As<Address*>()[index];
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	T GetMethod(uint32_t index)
	{
		return (T)GetMethod(index).Pointer();
	}

private:
	std::vector<Address> rawData;
	Address pVtable;
	Address* pNewVtable;
	Address pOldVtable;
	size_t sizeVtable;

	size_t GetVtableSize(Address pVtable);
};

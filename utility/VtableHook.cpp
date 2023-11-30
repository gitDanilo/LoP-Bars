// Modified from https://github.com/praydog/REFramework source code

#include "Memory.hpp"
#include "VtableHook.hpp"

VtableHook::VtableHook() : rawData(), pVtable(), pNewVtable(nullptr), pOldVtable(), sizeVtable(0)
{
}

VtableHook::VtableHook(Address target) : VtableHook()
{
	Create(target);
}

VtableHook::VtableHook(VtableHook&& other) : rawData(std::move(other.rawData)),
	pVtable(other.pVtable),
	pNewVtable(other.pNewVtable),
	pOldVtable(other.pOldVtable),
	sizeVtable(other.sizeVtable)
{
	other.pVtable = nullptr;
	other.pNewVtable = nullptr;
	other.pOldVtable = nullptr;
	other.sizeVtable = 0;
}

VtableHook::~VtableHook()
{
	Remove();
}

bool VtableHook::Create(Address target)
{
	if (!rawData.empty())
	{
		Remove();
		rawData.clear();
	}

	pVtable = target;
	pOldVtable = pVtable.To<Address>();
	sizeVtable = GetVtableSize(pOldVtable);
	// RTTI.
	rawData.resize(sizeVtable + 1);
	pNewVtable = rawData.data() + 1;

	memcpy(rawData.data(), pOldVtable.As<Address*>() - 1, sizeof(Address) * (sizeVtable + 1));

	// At this point we have the address of the old vtable, and a copy of it
	// stored in m_new_vtable.  Set the target objects vtable
	// pointer to our copy of the original.
	*pVtable.As<Address*>() = pNewVtable;

	return true;
}

bool VtableHook::Recreate()
{
	if (pVtable != nullptr)
	{
		*pVtable.As<Address*>() = pNewVtable;
		return true;
	}

	return false;
}

bool VtableHook::Remove()
{
	// Can cause issues where we set the vtable/random memory of some other pointer.
	if (pVtable != nullptr && utility::IsBadReadPtr(pVtable.Pointer()) == FALSE && pVtable.To<void*>() == pNewVtable)
	{
		*pVtable.As<Address*>() = pOldVtable;
		return true;
	}

	return false;
}

bool VtableHook::HookMethod(uint32_t index, Address newMethod)
{
	if (pOldVtable != nullptr && pNewVtable != nullptr && index < sizeVtable)
	{
		pNewVtable[index] = newMethod;
		return true;
	}

	return false;
}

size_t VtableHook::GetVtableSize(Address vtable)
{
	size_t i = 0;

	for (; vtable.As<Address*>()[i] != nullptr; ++i)
	{
		if (utility::IsBadReadPtr(vtable.As<FARPROC*>()[i]) == TRUE)
		{
			break;
		}
	}

	return i;
}

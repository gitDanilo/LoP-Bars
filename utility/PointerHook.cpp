// Modified from https://github.com/praydog/REFramework source code

#include <stdexcept>
#include <windows.h>
#include "Memory.hpp"
#include "PointerHook.hpp"
#include "Log.hpp"

ProtectionOverride::ProtectionOverride(void* pAddress, size_t size, uint32_t dwProtection) : pAddress(pAddress), size(size)
{
	if (!VirtualProtect(pAddress, size, dwProtection, (DWORD*)&dwOldProtection))
	{
		LOG_ERROR("ProtectionOverride failed to change protection params of " << std::hex << (uintptr_t)pAddress);
		throw std::runtime_error("VirtualProtect failed");
	}
}

ProtectionOverride::~ProtectionOverride()
{
	VirtualProtect(pAddress, size, dwOldProtection, (DWORD*)&dwOldProtection);
}


PointerHook::PointerHook(void** pOld, void* pNew)
{
	if (pOld == nullptr)
	{
		LOG_ERROR("PointerHook: pOld is nullptr");
		throw std::invalid_argument("pOld cannot be nullptr");
	}

	if (utility::IsBadReadPtr(pOld))
	{
		LOG_ERROR("PointerHook: pOld is not readable");
		throw std::invalid_argument("pOld is not readable");
	}

	ProtectionOverride overrider{ pOld, sizeof(void*), PAGE_EXECUTE_READWRITE };

	LOG_INFO("PointerHook Hooking " << std::hex << (uintptr_t)pOld << " -> " << (uintptr_t)pNew);

	pReplace = pOld;
	pDestination = pNew;
	pOriginal = *pOld;
	*pOld = pNew;
}

PointerHook::~PointerHook()
{
	Remove();
}

bool PointerHook::Remove()
{
	if (pReplace != nullptr && !utility::IsBadReadPtr(pReplace) && *pReplace == pDestination)
	{
		try
		{
			ProtectionOverride protectionOverride(pReplace, sizeof(void*), PAGE_EXECUTE_READWRITE);
			*pReplace = pOriginal;
		}
		catch (...)
		{
			LOG_ERROR("PointerHook failed to remove the hook.");
			return false;
		}
	}

	return true;
}

bool PointerHook::Restore()
{
	if (pReplace != nullptr && !utility::IsBadReadPtr(pReplace) && *pReplace != pDestination)
	{
		try
		{
			ProtectionOverride protectionOverride(pReplace, sizeof(void*), PAGE_EXECUTE_READWRITE);
			*pReplace = pDestination;
		}
		catch (...)
		{
			LOG_ERROR("PointerHook failed to restore the hook.");
			return false;
		}
	}

	return true;
}

// Modified from https://github.com/praydog/REFramework source code

#include <MinHook.h>
#include "Log.hpp"
#include "FunctionHook.hpp"

static bool gIsMinHookInitialized = false;

FunctionHook::FunctionHook(Address target, Address destination)
	: pTarget{ 0 },
	pDestination{ 0 },
	pOriginal{ 0 }
{
	LOG_INFO("Attempting to hook " << std::hex << target.Pointer() << " -> " << destination.Pointer());

	// Initialize MinHook if it hasn't been already.
	if (!gIsMinHookInitialized && MH_Initialize() == MH_OK)
	{
		gIsMinHookInitialized = true;
	}

	// Create the hook. Call create afterwards to prevent race conditions accessing FunctionHook before it leaves its constructor.
	if (auto status = MH_CreateHook(target.As<LPVOID>(), destination.As<LPVOID>(), (LPVOID*)&pOriginal); status == MH_OK)
	{
		pTarget = target;
		pDestination = destination;

		LOG_INFO("Hook init successful");
	}
	else
	{
		LOG_ERROR("Hook failed");
	}
}

FunctionHook::~FunctionHook()
{
	Remove();
}

bool FunctionHook::Create()
{
	if (pTarget == 0 || pDestination == 0 || pOriginal == 0)
	{
		LOG_WARNING("FunctionHook not initialized");
		return false;
	}

	if (auto status = MH_EnableHook((LPVOID)pTarget); status != MH_OK)
	{
		pOriginal = 0;
		pDestination = 0;
		pTarget = 0;

		LOG_ERROR("Failed to hook " << std::hex << pTarget << ": " << MH_StatusToString(status));
		return false;
	}

	LOG_INFO("Hooked " << std::hex << pTarget << " -> " << pDestination);
	return true;
}

bool FunctionHook::Remove()
{
	// Don't try to remove invalid hooks.
	if (pOriginal == 0)
	{
		return true;
	}

	// Disable then remove the hook.
	if (MH_DisableHook((LPVOID)pTarget) != MH_OK ||
		MH_RemoveHook((LPVOID)pTarget) != MH_OK)
	{
		return false;
	}

	// Invalidate the members.
	pTarget = 0;
	pDestination = 0;
	pOriginal = 0;

	return true;
}

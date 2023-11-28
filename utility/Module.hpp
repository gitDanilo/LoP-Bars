// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <string_view>
#include <functional>
#include <Windows.h>
#include "Address.hpp"

struct _LIST_ENTRY;
typedef struct _LIST_ENTRY LIST_ENTRY;

struct _LDR_DATA_TABLE_ENTRY;

namespace utility
{
	//
	// Module utilities.
	//
	std::optional<size_t> GetModuleSize(const std::wstring& module);
	std::optional<size_t> GetModuleSize(HMODULE module);
	std::optional<HMODULE> GetModuleWithin(Address address);
	std::optional<uintptr_t> GetDLLImageBase(Address dll);
	std::optional<uintptr_t> GetImageBaseVAFromPtr(Address dll, Address base, void* ptr);

	std::optional<std::string> GetModulePath(HMODULE module);
	std::optional<std::wstring> GetModulePathW(HMODULE module);
	std::optional<std::string> GetModuleDirectory(HMODULE module);
	std::optional<std::wstring> GetModuleDirectoryW(HMODULE module);
	HMODULE LoadModuleFromCurrentDirectory(const std::wstring& module);

	std::vector<uint8_t> ReadModuleFromDisk(HMODULE module);

	// Returns the original bytes of the module at the given address.
	// useful for un-patching something.
	std::optional<std::vector<uint8_t>> GetOriginalBytes(Address address);
	std::optional<std::vector<uint8_t>> GetOriginalBytes(HMODULE module, Address address);

	// Note: This function doesn't validate the dll's headers so make sure you've
	// done so before calling it.
	std::optional<uintptr_t> PtrFromRVA(uint8_t* dll, uintptr_t rva);

	HMODULE GetExecutable();
	HMODULE Unlink(HMODULE module);
	HMODULE SafeUnlink(HMODULE module);
	HMODULE FindPartialModule(std::wstring_view name);

	void ForEachModule(std::function<void(LIST_ENTRY*, _LDR_DATA_TABLE_ENTRY*)> callback);
	size_t GetModuleCount(std::wstring_view name);
}

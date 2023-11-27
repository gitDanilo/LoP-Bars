// Modified from https://github.com/praydog/REFramework source code

#define NOMINMAX

#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <mutex>
#include <shlwapi.h>
#include <windows.h>
#include <winternl.h>
#include "Log.hpp"
#include "String.hpp"
#include "Thread.hpp"
#include "Module.hpp"

#pragma comment(lib, "Shlwapi.lib")

namespace utility {
	std::optional<size_t> GetModuleSize(const std::wstring& module) {
		return GetModuleSize(GetModuleHandle(module.c_str()));
	}

	std::optional<size_t> GetModuleSize(HMODULE module) {
		if (module == nullptr) {
			return {};
		}

		// Get the dos header and verify that it seems valid.
		auto dosHeader = (PIMAGE_DOS_HEADER)module;

		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			return {};
		}

		// Get the nt headers and verify that they seem valid.
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uintptr_t)dosHeader + dosHeader->e_lfanew);

		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
			return {};
		}

		// OptionalHeader is not actually optional.
		return ntHeaders->OptionalHeader.SizeOfImage;
	}

	std::optional<HMODULE> GetModuleWithin(Address address) {
		HMODULE module = nullptr;
		if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, address.As<LPWSTR>(), &module)) {
			return module;
		}

		return {};
	}

	std::optional<uintptr_t> GetDLLImageBase(Address dll) {
		if (dll == nullptr) {
			return {};
		}

		// Get the dos header and verify that it seems valid.
		auto dosHeader = dll.As<PIMAGE_DOS_HEADER>();

		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			return {};
		}

		// Get the nt headers and verify that they seem valid.
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uintptr_t)dosHeader + dosHeader->e_lfanew);

		if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
			return {};
		}

		return ntHeaders->OptionalHeader.ImageBase;
	}

	std::optional<uintptr_t> GetImageBaseVAFromPtr(Address dll, Address base, void* ptr) {
		auto imgBase = GetDLLImageBase(dll);

		if (!imgBase) {
			return {};
		}

		return *imgBase + ((uintptr_t)ptr - base.As<uintptr_t>());
	}


	std::optional<std::string> GetModulePath(HMODULE module) {
		wchar_t sFilename[MAX_PATH] = { 0 };
		if (GetModuleFileNameW(module, sFilename, MAX_PATH) >= MAX_PATH) {
			return {};
		}

		return utility::narrow(sFilename);
	}

	std::optional<std::wstring> GetModulePathW(HMODULE module) {
		wchar_t sFilename[MAX_PATH] = { 0 };
		if (GetModuleFileNameW(module, sFilename, MAX_PATH) >= MAX_PATH) {
			return {};
		}

		return sFilename;
	}

	std::optional<std::string> GetModuleDirectory(HMODULE module) {
		wchar_t sFilename[MAX_PATH] = { 0 };
		if (GetModuleFileNameW(module, sFilename, MAX_PATH) >= MAX_PATH) {
			return {};
		}

		PathRemoveFileSpecW(sFilename);

		return utility::narrow(sFilename);
	}

	std::optional<std::wstring> GetModuleDirectoryW(HMODULE module) {
		wchar_t sFilename[MAX_PATH] = { 0 };
		if (GetModuleFileNameW(module, sFilename, MAX_PATH) >= MAX_PATH) {
			return {};
		}

		PathRemoveFileSpecW(sFilename);

		return sFilename;
	}

	HMODULE LoadModuleFromCurrentDirectory(const std::wstring& module) {
		const auto sCurrentPath = GetModuleDirectoryW(GetExecutable());

		if (!sCurrentPath) {
			return nullptr;
		}

		auto fsPath = std::filesystem::path{ *sCurrentPath } / module;

		return LoadLibraryW(fsPath.c_str());
	}

	std::vector<uint8_t> ReadModuleFromDisk(HMODULE module) {
		auto path = GetModulePath(module);

		if (!path) {
			return {};
		}

		// read using std utilities like ifstream and tellg, etc.
		auto file = std::ifstream{ path->c_str(), std::ios::binary | std::ios::ate };

		if (!file.is_open()) {
			return {};
		}

		auto size = file.tellg();
		file.seekg(0, std::ios::beg);

		// don't brace initialize std::vector because it won't
		// call the right constructor.
		auto data = std::vector<uint8_t>((size_t)size);
		file.read((char*)data.data(), size);

		return data;
	}

	std::optional<std::vector<uint8_t>> GetOriginalBytes(Address address) {
		auto moduleWithin = GetModuleWithin(address);

		if (!moduleWithin) {
			return {};
		}

		return GetOriginalBytes(*moduleWithin, address);
	}

	std::optional<std::vector<uint8_t>> GetOriginalBytes(HMODULE module, Address address) {
		auto disk_data = ReadModuleFromDisk(module);

		if (disk_data.empty()) {
			return std::nullopt;
		}

		auto moduleBase = GetDLLImageBase(module);

		if (!moduleBase) {
			return std::nullopt;
		}

		auto moduleRVA = address.As<uintptr_t>() - *moduleBase;

		// obtain the file offset of the address now
		auto pDisk = PtrFromRVA(disk_data.data(), moduleRVA);

		if (!pDisk) {
			return std::nullopt;
		}

		auto aobOriginal = std::vector<uint8_t>{};

		auto aobModule = address.As<uint8_t*>();
		auto aobDisk = (uint8_t*)*pDisk;

		// copy the bytes from the disk data to the original bytes
		// copy only until the bytes start to match eachother
		for (auto i = 0; ; ++i) {
			if (aobModule[i] == aobDisk[i]) {
				bool actually_matches = true;

				// Lookahead 4 bytes to check if any other part is different before breaking out.
				for (auto j = 1; j <= 4; ++j) {
					if (aobModule[i + j] != aobDisk[i + j]) {
						actually_matches = false;
						break;
					}
				}

				if (actually_matches) {
					break;
				}
			}

			aobOriginal.push_back(aobDisk[i]);
		}

		if (aobOriginal.empty()) {
			return std::nullopt;
		}

		return aobOriginal;
	}

	HMODULE GetExecutable() {
		return GetModuleHandle(nullptr);
	}

	std::mutex gUnlinkMutex{};

	HMODULE Unlink(HMODULE module)
	{
		std::scoped_lock _{ gUnlinkMutex };

		const auto base = (uintptr_t)module;

		if (base == 0) {
			return module;
		}

		// this SHOULD be thread safe...?
		ForEachModule([&](LIST_ENTRY* entry, _LDR_DATA_TABLE_ENTRY* ldr_entry)
		{
			if ((uintptr_t)ldr_entry->DllBase == base)
			{
				entry->Blink->Flink = entry->Flink;
				entry->Flink->Blink = entry->Blink;
			}
		});

		return module;
	}

	HMODULE SafeUnlink(HMODULE module)
	{
		if (module == nullptr)
		{
			return nullptr;
		}

		ThreadSuspender _{};

		Unlink(module);
		return module;
	}

	HMODULE FindPartialModule(std::wstring_view name)
	{
		HMODULE module = nullptr;

		ForEachModule([&](LIST_ENTRY* entry, _LDR_DATA_TABLE_ENTRY* ldr_entry)
		{
			if (module != nullptr)
			{
				return;
			}

			if (std::wstring_view{ ldr_entry->FullDllName.Buffer }.find(name) != std::wstring_view::npos)
			{
				module = (HMODULE)ldr_entry->DllBase;
			}
		});

		return module;
	}

	void ForEachModule(std::function<void(LIST_ENTRY*, _LDR_DATA_TABLE_ENTRY*)> callback) try
	{
		if (!callback)
		{
			return;
		}

		auto peb = (PEB*)__readgsqword(0x60);

		if (peb == nullptr)
		{
			return;
		}

		for (auto entry = peb->Ldr->InMemoryOrderModuleList.Flink; entry != &peb->Ldr->InMemoryOrderModuleList && entry != nullptr; entry = entry->Flink)
		{
			if (IsBadReadPtr(entry, sizeof(LIST_ENTRY)))
			{
				break;
			}

			auto ldr_entry = (_LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(entry, _LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

			if (IsBadReadPtr(ldr_entry, sizeof(_LDR_DATA_TABLE_ENTRY)))
			{
				break;
			}

			callback(entry, ldr_entry);
		}
	}
	catch (std::exception& e)
	{
		LOG_ERROR("Exception while iterating modules: " << e.what());
	}
	catch (...)
	{
		LOG_ERROR("Unexpected exception while iterating modules. Continuing...");
	}

	size_t GetModuleCount(std::wstring_view name)
	{
		size_t out{};

		wchar_t sLowerName[MAX_PATH] = { 0 };
		std::transform(name.begin(), name.end(), sLowerName, ::towlower);

		ForEachModule([&](LIST_ENTRY* entry, _LDR_DATA_TABLE_ENTRY* ldr_entry)
		{
			wchar_t sLowerDLLName[MAX_PATH] = { 0 };
			std::transform(ldr_entry->FullDllName.Buffer, ldr_entry->FullDllName.Buffer + ldr_entry->FullDllName.Length, sLowerDLLName, ::towlower);

			if (std::wstring_view{ sLowerDLLName }.find(sLowerName) != std::wstring_view::npos)
			{
				++out;
			}
		});

		return out;
	}

	std::optional<uintptr_t> PtrFromRVA(uint8_t* dll, uintptr_t rva)
	{
		// Get the first section.
		auto dosHeader = (PIMAGE_DOS_HEADER)&dll[0];
		auto ntHeaders = (PIMAGE_NT_HEADERS)&dll[dosHeader->e_lfanew];
		auto section = IMAGE_FIRST_SECTION(ntHeaders);

		// Go through each section searching for where the rva lands.
		for (uint16_t i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i, ++section)
		{
			auto size = section->Misc.VirtualSize;

			if (size == 0) {
				size = section->SizeOfRawData;
			}

			if (rva >= section->VirtualAddress && rva < ((uintptr_t)section->VirtualAddress + size))
			{
				auto delta = section->VirtualAddress - section->PointerToRawData;

				return (uintptr_t)(dll + (rva - delta));
			}
		}

		return {};
	}
}

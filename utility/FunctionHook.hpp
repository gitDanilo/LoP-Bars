// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <windows.h>
#include <cstdint>
#include "Address.hpp"

class FunctionHook
{
public:
	FunctionHook() = delete;
	FunctionHook(const FunctionHook& other) = delete;
	FunctionHook(FunctionHook&& other) = delete;
	FunctionHook(Address target, Address destination);
	virtual ~FunctionHook();

	bool Create();

	// Called automatically by the destructor, but you can call it explicitly
	// if you need to remove the hook.
	bool Remove();

	auto GetOriginal() const
	{
		return pOriginal;
	}

	template <typename T>
	T* GetOriginal() const
	{
		return (T*)pOriginal;
	}

	auto IsValid() const
	{
		return pOriginal != 0;
	}

	FunctionHook& operator=(const FunctionHook& other) = delete;
	FunctionHook& operator=(FunctionHook&& other) = delete;

private:
	void* pTarget = nullptr;
	void* pDestination = nullptr;
	void* pOriginal = nullptr;
};

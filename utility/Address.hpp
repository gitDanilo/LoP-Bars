// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <string>
#include <cstdint>

// sizeof(Address) should always be sizeof(void*).
class Address
{
public:
	Address();
	Address(void* ptr);
	Address(uintptr_t addr);

	void Set(void* ptr)
	{
		ptr = ptr;
	}

	template <typename T>
	Address Get(T offset) const
	{
		return Address((uintptr_t)ptr + offset);
	}

	template <typename T>
	Address Add(T offset) const
	{
		return Address((uintptr_t)ptr + offset);
	}

	template <typename T>
	Address Sub(T offset) const
	{
		return Address((uintptr_t)ptr - offset);
	}

	template <typename T>
	T As() const
	{
		return (T)ptr;
	}

	// to is like as but dereferences that shit.
	template <typename T>
	T To() const
	{
		return *(T*)ptr;
	}

	Address Deref() const
	{
		return To<void*>();
	}

	void* Pointer() const
	{
		return ptr;
	}

	operator uintptr_t() const
	{
		return (uintptr_t)ptr;
	}

	operator void* () const
	{
		return ptr;
	}

	bool operator ==(bool val)
	{
		return ((ptr && val) || (!ptr && !val));
	}

	bool operator !=(bool val)
	{
		return !(*this == val);
	}

	bool operator ==(uintptr_t val)
	{
		return ((uintptr_t)ptr == val);
	}

	bool operator !=(uintptr_t val)
	{
		return !(*this == val);
	}

	bool operator ==(void* val)
	{
		return (ptr == val);
	}

	bool operator !=(void* val)
	{
		return !(*this == val);
	}

private:
	void* ptr;
};

typedef Address Offset;

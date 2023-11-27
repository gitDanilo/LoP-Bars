// Modified from https://github.com/praydog/REFramework source code

#include <cstdio>
#include "Address.hpp"

Address::Address() : ptr(nullptr)
{
}

Address::Address(void* ptr) : ptr(ptr)
{
}

Address::Address(uintptr_t addr) : ptr((void*)addr)
{
}

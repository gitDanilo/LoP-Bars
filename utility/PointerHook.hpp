// Modified from https://github.com/praydog/REFramework source code

#pragma once

class ProtectionOverride
{
public:
	ProtectionOverride(void* pAddress, size_t size, uint32_t dwProtectionParams);
	virtual ~ProtectionOverride();
private:
	void* pAddress;
	size_t size;
	uint32_t dwOldProtection;
};

class PointerHook
{
public:
	PointerHook(void** pOld, void* pNew);
	virtual ~PointerHook();

	bool Remove();
	bool Restore();

	template<typename T>
	T GetOriginal() const
	{
		return (T)pOriginal;
	}

private:
	void** pReplace;
	void* pOriginal;
	void* pDestination;
};

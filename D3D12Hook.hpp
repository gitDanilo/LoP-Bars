// Modified from https://github.com/praydog/REFramework source code

#pragma once

#include <iostream>
#include <functional>
#include <mutex>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi")

#include <d3d12.h>
#include <dxgi1_4.h>
#include "utility/PointerHook.hpp"
#include "utility/VtableHook.hpp"

class D3D12Hook
{
public:
	typedef std::function<void()> OnEventCallback;

	static D3D12Hook& GetInstance()
	{
		static D3D12Hook instance;
		return instance;
	}
	virtual ~D3D12Hook();

	D3D12Hook(const D3D12Hook& other) = delete;
	D3D12Hook(D3D12Hook&& other) = delete;

	D3D12Hook& operator=(const D3D12Hook& other) = delete;
	D3D12Hook& operator=(const D3D12Hook&& other) = delete;

	bool Hook();
	bool Unhook();
	bool IsHooked() { return bIsHooked; }
	
	void SetOnPresent(OnEventCallback function) { fnOnPresent = function; }
	void SetOnPostPresent(OnEventCallback function) { fnOnPostPresent = function; }
	void SetOnResizeBuffers(OnEventCallback function) { fnOnResizeBuffers = function; }
	void SetOnResizeTarget(OnEventCallback function) { fnOnResizeTarget = function; }

	ID3D12Device4* GetDevice() const { return pDevice; }
	IDXGISwapChain3* GetSwapChain() const { return pSwapChain; }
	ID3D12CommandQueue* GetCommandQueue() const { return pCommandQueue; }
	UINT GetDisplayWidth() const { return displayWidth; }
	UINT GetDisplayHeight() const { return displayHeight; }
	UINT GetRenderWidth() const { return renderWidth; }
	UINT GetRenderHeight() const { return renderHeight; }
	bool IsInsidePresent() const { return bIsInsidePresent; }
	void IgnoreNextPresent() { bIgnoreNextPresent = true; }
private:
	D3D12Hook() = default;

	ID3D12Device4* pDevice = nullptr;
	IDXGISwapChain3* pSwapChain = nullptr;
	IDXGISwapChain3* pSwapChain0 = nullptr;
	IDXGISwapChain3* pSwapChain1 = nullptr;
	ID3D12CommandQueue* pCommandQueue = nullptr;
	UINT displayWidth = 0;
	UINT displayHeight = 0;
	UINT renderWidth = 0;
	UINT renderHeight = 0;

	uint32_t dwCommandQueueOffset = 0;
	uint32_t dwProtonSwapChainOffset = 0;

	bool bIsHooked = false;
	bool bIsPhase1 = true;
	bool bIsInsidePresent = false;
	bool bIgnoreNextPresent = false;
	bool bIsProtonSwapChain = false;

	std::unique_ptr<PointerHook> pPresentPtrHook;
	std::unique_ptr<VtableHook> pSwapChainVTableHook;

	OnEventCallback fnOnPresent = nullptr;
	OnEventCallback fnOnPostPresent = nullptr;
	OnEventCallback fnOnResizeBuffers = nullptr;
	OnEventCallback fnOnResizeTarget = nullptr;

	static HRESULT WINAPI Present(IDXGISwapChain3* pSwapChain, UINT dwSyncInterval, UINT dwFlags);
	static HRESULT WINAPI ResizeBuffers(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static HRESULT WINAPI ResizeTarget(IDXGISwapChain3* pSwapChain, const DXGI_MODE_DESC* pNewTargetParameters);
};

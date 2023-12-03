#pragma once

#include <memory>
#include <mutex>
#include <array>
#include <wrl.h>
#include "D3D12HOOK.hpp"
#include "WindowsMessageHook.hpp"
#include "ImGuiWindow.hpp"

#define MAX_INIT_ATTEMPTS 3

template <typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;

typedef struct _D3D12_FRAME_CONTEXT
{
	ComPtr<ID3D12Resource> pRTV;
	D3D12_CPU_DESCRIPTOR_HANDLE hCPUDesc;
} *PD3D12_FRAME_CONTEXT, D3D12_FRAME_CONTEXT;

typedef struct _D3D12_INTERFACE
{
	std::vector<D3D12_FRAME_CONTEXT> frameContexts;

	ComPtr<ID3D12DescriptorHeap> pRTVHeapDesc;
	ComPtr<ID3D12DescriptorHeap> pSRVHeapDesc;
	ComPtr<ID3D12CommandAllocator> pCmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> pCmdList;
} *PD3D12_INTERFACE, D3D12_INTERFACE;

class LoPBars
{
public:
	static LoPBars& GetInstance()
	{
		static LoPBars instance;
		return instance;
	}
	virtual ~LoPBars();

	LoPBars(const LoPBars& other) = delete;
	LoPBars(LoPBars&& other) = delete;

	LoPBars& operator=(const LoPBars& other) = delete;
	LoPBars& operator=(const LoPBars&& other) = delete;
private:
	LoPBars();
	HWND hWnd;
	D3D12_INTERFACE iD3D12;
	std::vector<std::unique_ptr<ImGuiWindow>> imGuiWindows;
	bool bIsInitialized;
	int initAttemptCount;
	bool HookD3D12();
	bool HookWindowsMsg();
	bool Initialize();
	void Cleanup();
	void ConfigImGui();
	bool InitializeD3D12();
	void OnPresentD3D12();
	void OnPostPresentD3D12();
	void OnDeviceReset();
	bool OnWindowsMsg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

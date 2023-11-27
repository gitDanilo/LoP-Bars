// Modified from https://github.com/praydog/REFramework source code

#include <thread>
#include <future>
#include <unordered_set>
#include "utility/Log.hpp"
#include "utility/Thread.hpp"
#include "utility/Module.hpp"
#include "WindowFilter.hpp"
#include "D3D12Hook.hpp"

D3D12Hook::~D3D12Hook()
{
	Unhook();
}

bool D3D12Hook::Hook()
{
	LOG_INFO("Hooking D3D12...");

	IDXGISwapChain1* pSwapChain1 = nullptr;
	IDXGISwapChain3* pSwapChain = nullptr;
	ID3D12Device* pDevice = nullptr;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc1 = {};
	swapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc1.BufferCount = 2;
	swapChainDesc1.SampleDesc.Count = 1;
	swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
	swapChainDesc1.Width = 1;
	swapChainDesc1.Height = 1;

	const HMODULE hD3D12Module = LoadLibraryA("d3d12.dll");
	if (hD3D12Module == nullptr)
	{
		LOG_ERROR("Failed to load d3d12.dll");
		return false;
	}

	auto fnD3D12CreateDevice = (decltype(D3D12CreateDevice)*)GetProcAddress(hD3D12Module, "D3D12CreateDevice");
	if (fnD3D12CreateDevice == nullptr)
	{
		LOG_ERROR("Failed to get D3D12CreateDevice export");
		return false;
	}

	LOG_INFO("Creating dummy device...");

	// Get the original on-disk bytes of the D3D12CreateDevice export
	const auto aobOriginal = utility::GetOriginalBytes(fnD3D12CreateDevice);

	// Temporarily unhook D3D12CreateDevice
	// it allows compatibility with ReShade and other overlays that hook it
	// this is just a dummy device anyways, we don't want the other overlays to be able to use it
	if (aobOriginal)
	{
		LOG_INFO("D3D12CreateDevice appears to be hooked, temporarily unhooking...");

		std::vector<uint8_t> aobHooked(aobOriginal->size());
		memcpy(aobHooked.data(), fnD3D12CreateDevice, aobOriginal->size());

		ProtectionOverride protectionOverride(fnD3D12CreateDevice, aobOriginal->size(), PAGE_EXECUTE_READWRITE);
		memcpy(fnD3D12CreateDevice, aobOriginal->data(), aobOriginal->size());

		if (FAILED(fnD3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&pDevice))))
		{
			LOG_ERROR("Failed to create dummy device");
			memcpy(fnD3D12CreateDevice, aobHooked.data(), aobHooked.size());
			return false;
		}

		LOG_INFO("Restoring hooked bytes for D3D12CreateDevice");
		memcpy(fnD3D12CreateDevice, aobHooked.data(), aobHooked.size());
	}
	else
	{ // D3D12CreateDevice is not hooked
		if (FAILED(fnD3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&pDevice))))
		{
			LOG_ERROR("Failed to create dummy device");
			return false;
		}
	}

	LOG_INFO("Dummy device: " << std::hex << (uintptr_t)pDevice);

	// Manually get CreateDXGIFactory export because the user may be running Windows 7
	const HMODULE hDXGIModule = LoadLibraryA("dxgi.dll");
	if (hDXGIModule == nullptr)
	{
		LOG_ERROR("Failed to load dxgi.dll");
		return false;
	}

	auto fnCreateDXGIFactory = (decltype(CreateDXGIFactory)*)GetProcAddress(hDXGIModule, "CreateDXGIFactory");

	if (fnCreateDXGIFactory == nullptr)
	{
		LOG_ERROR("Failed to get CreateDXGIFactory export");
		return false;
	}

	LOG_INFO("Creating dummy DXGI factory...");

	IDXGIFactory4* factory = nullptr;
	if (FAILED(fnCreateDXGIFactory(IID_PPV_ARGS(&factory))))
	{
		LOG_ERROR("Failed to create dummy DXGIFactory");
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	cmdQueueDesc.Priority = 0;
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	cmdQueueDesc.NodeMask = 0;

	LOG_INFO("Creating dummy CommandQueue...");

	ID3D12CommandQueue* pCommandQueue = nullptr;
	if (FAILED(pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&pCommandQueue))))
	{
		LOG_ERROR("Failed to create dummy CommandQueue");
		return false;
	}

	LOG_INFO("Creating dummy SwapChain...");

	// used in CreateSwapChainForHwnd fallback
	HWND hwnd = 0;
	WNDCLASSEX wc = {};

	auto fnInitDummyWindow = [&]()
		{
			// fallback to CreateSwapChainForHwnd
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = DefWindowProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = GetModuleHandle(NULL);
			wc.hIcon = NULL;
			wc.hCursor = NULL;
			wc.hbrBackground = NULL;
			wc.lpszMenuName = NULL;
			wc.lpszClassName = TEXT("LOPBARS_DX12_DUMMY");
			wc.hIconSm = NULL;

			::RegisterClassEx(&wc);

			hwnd = ::CreateWindow(wc.lpszClassName, TEXT("REF DX Dummy Window"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, wc.hInstance, NULL);

			swapChainDesc1.BufferCount = 3;
			swapChainDesc1.Width = 0;
			swapChainDesc1.Height = 0;
			swapChainDesc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
			swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc1.SampleDesc.Count = 1;
			swapChainDesc1.SampleDesc.Quality = 0;
			swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			swapChainDesc1.Scaling = DXGI_SCALING_STRETCH;
			swapChainDesc1.Stereo = FALSE;
		};

	std::vector<std::function<bool()>> swapChainAttempts
	{
		// we call CreateSwapChainForComposition instead of CreateSwapChainForHwnd
		// because some overlays will have hooks on CreateSwapChainForHwnd
		// and all we're doing is creating a dummy swapchain
		// we don't want to screw up the overlay
		[&]()
		{
			return !FAILED(factory->CreateSwapChainForComposition(pCommandQueue, &swapChainDesc1, nullptr, &pSwapChain1));
		},
		[&]()
		{
			fnInitDummyWindow();
			return !FAILED(factory->CreateSwapChainForHwnd(pCommandQueue, hwnd, &swapChainDesc1, nullptr, nullptr, &pSwapChain1));
		},
		[&]()
		{
			return !FAILED(factory->CreateSwapChainForHwnd(pCommandQueue, GetDesktopWindow(), &swapChainDesc1, nullptr, nullptr, &pSwapChain1));
		},
	};

	bool bAnySucceed = false;

	for (auto i = 0; i < swapChainAttempts.size(); ++i)
	{
		auto& attempt = swapChainAttempts[i];

		try
		{
			LOG_INFO("Trying swapchain attempt " << i);

			if (attempt())
			{
				LOG_INFO("Created dummy SwapChain on attempt " << i);
				bAnySucceed = true;
				break;
			}
		}
		catch (std::exception& e)
		{
			LOG_ERROR("Failed to create dummy SwapChain on attempt " << i << ": " << e.what());
		}
		catch (...)
		{
			LOG_ERROR("Failed to create dummy SwapChain on attempt " << i << " unknown exception");
		}

		LOG_ERROR("Attempt " << i << " failed");
	}

	if (!bAnySucceed)
	{
		LOG_ERROR("Failed to create dummy SwapChain");

		if (hwnd)
		{
			::DestroyWindow(hwnd);
		}

		if (wc.lpszClassName != nullptr)
		{
			::UnregisterClass(wc.lpszClassName, wc.hInstance);
		}

		return false;
	}

	LOG_INFO("Querying dummy SwapChain...");

	if (FAILED(pSwapChain1->QueryInterface(IID_PPV_ARGS(&pSwapChain))))
	{
		LOG_ERROR("Failed to retrieve SwapChain");
		return false;
	}

	LOG_INFO("Finding CommandQueue offset...");

	// Find the command queue offset in the swapchain
	for (auto i = 0; i < 512 * sizeof(void*); i += sizeof(void*))
	{
		const auto base = (uintptr_t)pSwapChain1 + i;

		// reached the end
		if (IsBadReadPtr((void*)base, sizeof(void*)))
		{
			break;
		}

		auto data = *(ID3D12CommandQueue**)base;

		if (data == pCommandQueue)
		{
			dwCommandQueueOffset = i;
			LOG_INFO("Found CommandQueue offset: " << i);
			break;
		}
	}

	if (dwCommandQueueOffset == 0)
	{
		LOG_ERROR("Failed to find CommandQueue offset");
		return false;
	}

	utility::ThreadSuspender threadSuspender;

	try
	{
		LOG_INFO("Initializing hooks...");

		pPresentPtrHook.reset();
		pSwapChainVTableHook.reset();

		bIsPhase1 = true;

		auto& fnPresent = (*(void***)pSwapChain)[8]; // Present
		auto& fnResizeBuffers = (*(void***)pSwapChain)[13]; // ResizeBuffers
		auto& fnResizeTargets = (*(void***)pSwapChain)[14]; // ResizeTarget
		pPresentPtrHook = std::make_unique<PointerHook>(&fnPresent, (void*)&D3D12Hook::Present);
		bIsHooked = true;
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("Failed to initialize hooks: " << e.what());
		bIsHooked = false;
	}

	threadSuspender.ResumeAll();

	pDevice->Release();
	pCommandQueue->Release();
	factory->Release();
	pSwapChain1->Release();
	pSwapChain->Release();

	if (hwnd)
	{
		::DestroyWindow(hwnd);
	}

	if (wc.lpszClassName != nullptr)
	{
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
	}

	return bIsHooked;
}

bool D3D12Hook::Unhook()
{
	if (!bIsHooked)
	{
		return false;
	}

	LOG_INFO("Unhooking D3D12...");

	pPresentPtrHook.reset();
	pSwapChainVTableHook.reset();

	pDevice = nullptr;
	pSwapChain = nullptr;
	pSwapChain0 = nullptr;
	pSwapChain1 = nullptr;
	pCommandQueue = nullptr;
	displayWidth = 0;
	displayHeight = 0;
	renderWidth = 0;
	renderHeight = 0;
	dwCommandQueueOffset = 0;
	bIsHooked = false;
	bIsPhase1 = true;
	bIsInsidePresent = false;
	bIgnoreNextPresent = false;

	return true;
}

thread_local int32_t gPresentDepth = 0;

HRESULT WINAPI D3D12Hook::Present(IDXGISwapChain3* pSwapChain, UINT dwSyncInterval, UINT dwFlags)
{
	auto& hkD3D12 = D3D12Hook::GetInstance();

	HWND hSwapChainWnd = nullptr;
	pSwapChain->GetHwnd(&hSwapChainWnd);

	decltype(D3D12Hook::Present)* fnPresent = nullptr;

	fnPresent = hkD3D12.pPresentPtrHook->GetOriginal<decltype(D3D12Hook::Present)*>();

	if (hkD3D12.bIsPhase1 && WindowFilter::GetInstance().IsFiltered(hSwapChainWnd))
	{
		return fnPresent(pSwapChain, dwSyncInterval, dwFlags);
	}

	if (!hkD3D12.bIsPhase1 && pSwapChain != hkD3D12.pSwapChainVTableHook->GetInstance())
	{
		return fnPresent(pSwapChain, dwSyncInterval, dwFlags);
	}

	if (hkD3D12.bIsPhase1)
	{
		// vtable hook the swapchain instead of global hooking
		// this seems safer for whatever reason
		// if we globally hook the vtable pointers, it causes all sorts of weird conflicts with other hooks
		// dont hook present though via this hook so other hooks dont get confused
		hkD3D12.pSwapChainVTableHook = std::make_unique<VtableHook>(pSwapChain);
		//hkD3D12.m_swapchain_hook->hook_method(8, (uintptr_t)&D3D12Hook::Present);
		hkD3D12.pSwapChainVTableHook->HookMethod(13, (uintptr_t)&D3D12Hook::ResizeBuffers);
		hkD3D12.pSwapChainVTableHook->HookMethod(14, (uintptr_t)&D3D12Hook::ResizeTarget);
		hkD3D12.bIsPhase1 = false;
	}

	hkD3D12.bIsInsidePresent = true;
	hkD3D12.pSwapChain = pSwapChain;

	pSwapChain->GetDevice(IID_PPV_ARGS(&hkD3D12.pDevice));

	if (hkD3D12.pDevice != nullptr)
	{
		hkD3D12.pCommandQueue = *(ID3D12CommandQueue**)((uintptr_t)pSwapChain + hkD3D12.dwCommandQueueOffset);
	}

	if (hkD3D12.pSwapChain0 == nullptr)
	{
		hkD3D12.pSwapChain0 = pSwapChain;
	}
	else if (hkD3D12.pSwapChain1 == nullptr && pSwapChain != hkD3D12.pSwapChain0)
	{
		hkD3D12.pSwapChain1 = pSwapChain;
	}

	// Restore the original bytes
	// if an infinite loop occurs, this will prevent the game from crashing
	// while keeping our hook intact
	if (gPresentDepth > 0)
	{
		auto aobOriginal = utility::GetOriginalBytes(Address(fnPresent));

		if (aobOriginal)
		{
			ProtectionOverride protectionOverride (fnPresent, aobOriginal->size(), PAGE_EXECUTE_READWRITE);

			memcpy(fnPresent, aobOriginal->data(), aobOriginal->size());

			LOG_INFO("Present fixed");
		}

		if ((uintptr_t)fnPresent != (uintptr_t)D3D12Hook::Present && gPresentDepth == 1)
		{
			LOG_INFO("Attempting to call real present function");

			++gPresentDepth;
			const auto result = fnPresent(pSwapChain, dwSyncInterval, dwFlags);
			--gPresentDepth;

			if (result != S_OK)
			{
				LOG_ERROR("Present failed: " << result);
			}

			return result;
		}

		LOG_INFO("Just returning S_OK");
		return S_OK;
	}

	if (hkD3D12.fnOnPresent)
	{
		hkD3D12.fnOnPresent();
	}

	++gPresentDepth;

	auto result = S_OK;

	if (!hkD3D12.bIgnoreNextPresent)
	{
		result = fnPresent(pSwapChain, dwSyncInterval, dwFlags);

		if (result != S_OK)
		{
			LOG_ERROR("Present failed: " << result);
		}
	}
	else
	{
		hkD3D12.bIgnoreNextPresent = false;
	}

	--gPresentDepth;

	if (hkD3D12.fnOnPostPresent)
	{
		hkD3D12.fnOnPostPresent();
	}

	hkD3D12.bIsInsidePresent = false;

	return result;
}

thread_local int32_t gResizeBuffersDepth = 0;

HRESULT WINAPI D3D12Hook::ResizeBuffers(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	LOG_INFO("D3D12 ResizeBuffers: BufferCount = " << std::dec << BufferCount << ", Width = " << Width << ", Heigth = " << Height);

	auto& hkD3D12 = D3D12Hook::GetInstance();

	HWND hSwapChainWnd = nullptr;
	pSwapChain->GetHwnd(&hSwapChainWnd);

	auto fnResizeBuffers = hkD3D12.pSwapChainVTableHook->GetMethod<decltype(D3D12Hook::ResizeBuffers)*>(13);

	hkD3D12.displayWidth = Width;
	hkD3D12.displayHeight = Height;

	if (gResizeBuffersDepth > 0)
	{
		const auto aobOriginal = utility::GetOriginalBytes(Address(fnResizeBuffers));

		if (aobOriginal)
		{
			ProtectionOverride protection_override (fnResizeBuffers, aobOriginal->size(), PAGE_EXECUTE_READWRITE);

			memcpy(fnResizeBuffers, aobOriginal->data(), aobOriginal->size());

			LOG_INFO("Resize buffers fixed");
		}

		if ((uintptr_t)fnResizeBuffers != (uintptr_t)&D3D12Hook::ResizeBuffers && gResizeBuffersDepth == 1)
		{
			LOG_INFO("Attempting to call the real resize buffers function");

			++gResizeBuffersDepth;
			const auto result = fnResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
			--gResizeBuffersDepth;

			if (result != S_OK)
			{
				LOG_ERROR("Resize buffers failed: " << std::hex << result);
			}

			return result;
		}
		else
		{
			LOG_INFO("Just returning S_OK");
			return S_OK;
		}
	}

	if (hkD3D12.fnOnResizeBuffers)
	{
		hkD3D12.fnOnResizeBuffers();
	}

	++gResizeBuffersDepth;

	const auto result = fnResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	if (result != S_OK)
	{
		LOG_ERROR("Resize buffers failed: " << std::hex << result);
	}

	--gResizeBuffersDepth;

	return result;
}

thread_local int32_t gResizeTargetDepth = 0;

HRESULT WINAPI D3D12Hook::ResizeTarget(IDXGISwapChain3* pSwapChain, const DXGI_MODE_DESC* pNewTargetParameters)
{
	LOG_INFO("D3D12 ResizeTarget: newTargetParams = " << std::hex << (uintptr_t)pNewTargetParameters);

	auto& hkD3D12 = D3D12Hook::GetInstance();

	HWND hSwapChainWnd = nullptr;
	pSwapChain->GetHwnd(&hSwapChainWnd);

	auto fnResizeTarget = hkD3D12.pSwapChainVTableHook->GetMethod<decltype(D3D12Hook::ResizeTarget)*>(14);

	hkD3D12.renderWidth = pNewTargetParameters->Width;
	hkD3D12.renderHeight = pNewTargetParameters->Height;

	// Restore the original code to the resize_buffers function.
	if (gResizeTargetDepth > 0)
	{
		const auto aobOriginal = utility::GetOriginalBytes(Address(fnResizeTarget));

		if (aobOriginal)
		{
			ProtectionOverride protectionOverride (fnResizeTarget, aobOriginal->size(), PAGE_EXECUTE_READWRITE);

			memcpy(fnResizeTarget, aobOriginal->data(), aobOriginal->size());

			LOG_INFO("Resize target fixed");
		}

		if ((uintptr_t)fnResizeTarget != (uintptr_t)&D3D12Hook::ResizeTarget && gResizeTargetDepth == 1)
		{
			LOG_INFO("Attempting to call the real resize target function");

			++gResizeTargetDepth;
			const auto result = fnResizeTarget(pSwapChain, pNewTargetParameters);
			--gResizeTargetDepth;

			if (result != S_OK)
			{
				LOG_ERROR("Resize target failed: " << std::hex << result);
			}

			return result;
		}
		else
		{
			LOG_INFO("Just returning S_OK");
			return S_OK;
		}
	}

	if (hkD3D12.fnOnResizeTarget)
	{
		hkD3D12.fnOnResizeTarget();
	}

	++gResizeTargetDepth;

	const auto result = fnResizeTarget(pSwapChain, pNewTargetParameters);

	if (result != S_OK)
	{
		LOG_ERROR("Resize target failed: " << std::hex << result);
	}

	--gResizeTargetDepth;

	return result;
}

#include "WinApp.h"

WinApp::WinApp(const unsigned int WindowH, const unsigned int WindowW)
{
	HINSTANCE hInst = GetModuleHandle(nullptr);
	//ウィンドウクラス生成＆登録
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;
	w.lpszClassName = _T("DirectXTest");
	w.hInstance = GetModuleHandle(0);
	RegisterClassEx(&w);

	RECT wrc = { 0,0, WindowW, WindowH };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);
	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(w.lpszClassName,
		_T("DX12テスト"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

#ifdef _DEBUG
	//デバッグレイヤーをオンに
	//EnableDebugLayer();
#endif
	//DirectX12初期化
	//フィーチャレベル列挙
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	HRESULT result = S_OK;
	if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&dxgiFactory_)))) {
		if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&dxgiFactory_)))) {
			exit;
		}
	}
	vector <IDXGIAdapter*> adapters;
	IDXGIAdapter* tmpAdapter = nullptr;
	for (int i = 0; dxgiFactory_->EnumAdapters(i, &tmpAdapter) != DXGI_ERROR_NOT_FOUND; ++i) {
		adapters.push_back(tmpAdapter);
	}
	for (auto adpt : adapters) {
		DXGI_ADAPTER_DESC adesc = {};
		adpt->GetDesc(&adesc);
		std::wstring strDesc = adesc.Description;
		if (strDesc.find(L"NVIDIA") != std::string::npos) {
			tmpAdapter = adpt;
			break;
		}
	}

	//Direct3Dデバイスの初期化
	D3D_FEATURE_LEVEL featureLevel;
	for (auto l : levels) {
		if (D3D12CreateDevice(tmpAdapter, l, IID_PPV_ARGS(&dev_)) == S_OK) {
			featureLevel = l;
			break;
		}
	}

	result = dev_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAllocator_));
	result = dev_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAllocator_, nullptr, IID_PPV_ARGS(&cmdList_));
	//_cmdList->Close();
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//タイムアウトなし
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//プライオリティ特に指定なし
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//ここはコマンドリストと合わせてください
	result = dev_->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue_));//コマンドキュー生成

	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = window_width;
	swapchainDesc.Height = window_height;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.Stereo = false;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	result = dxgiFactory_->CreateSwapChainForHwnd(cmdQueue_,
		hwnd,
		&swapchainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapchain_);

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビューなので当然RTV
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = 2;//表裏の２つ
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし

	result = dev_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));
	result = swapchain_->GetDesc(&swcDesc);
	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
	for (size_t i = 0; i < swcDesc.BufferCount; ++i) {
		result = swapchain_->GetBuffer(static_cast<UINT>(i), IID_PPV_ARGS(&_backBuffers[i]));
		dev_->CreateRenderTargetView(_backBuffers[i], nullptr, handle);
		handle.ptr += dev_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	result = dev_->CreateFence(_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));

	ShowWindow(hwnd, SW_SHOW);//ウィンドウ表示
}

WinApp::~WinApp()
{
	//クラス登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}

/// <summary>
/// 背景色の設定
/// </summary>
/// <param name="r">red</param>
/// <param name="g">green</param>
/// <param name="b">blue</param>
/// <param name="a">alfa</param>
void WinApp::SetBackColor(int r, int g, int b, float a)
{
	clearColor[0] = r / 255.f;
	clearColor[1] = g / 255.f;
	clearColor[2] = b / 255.f;
	clearColor[3] = a;
}

void WinApp::SetWindowSize(const unsigned int winw, const unsigned int winh)
{
	window_width = winw;
	window_height = winh;
}

void WinApp::DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	printf(format, valist);
	va_end(valist);
#endif // _DEBUG
}

void WinApp::EnableDebugLayer() {
	ID3D12Debug* debugLayer = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer)))) {
		debugLayer->EnableDebugLayer();
		debugLayer->Release();
	}
}
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_DESTROY) {//ウィンドウが破棄されたら呼ばれます
		PostQuitMessage(0);//OSに対して「もうこのアプリは終わるんや」と伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//規定の処理を行う
}
void WinApp::PreUpdate()
{
	//DirectX処理
	//バックバッファのインデックスを取得
	auto bbIdx = swapchain_->GetCurrentBackBufferIndex();

	D3D12_RESOURCE_BARRIER BarrierDesc = {};
	BarrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	BarrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	BarrierDesc.Transition.pResource = _backBuffers[bbIdx];
	BarrierDesc.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	cmdList_->ResourceBarrier(1, &BarrierDesc);

	//レンダーターゲットを指定
	auto rtvH = rtvHeaps->GetCPUDescriptorHandleForHeapStart();
	rtvH.ptr += static_cast<ULONG_PTR>(bbIdx * dev_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
	cmdList_->OMSetRenderTargets(1, &rtvH, false, nullptr);

	//画面クリア
	//float clearColor[] = { 0.5f,0.5f,0.5f,1.0f };//黄色
	cmdList_->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);

	BarrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	BarrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	cmdList_->ResourceBarrier(1, &BarrierDesc);

}

void WinApp::PostUpdate()
{
	//命令のクローズ
	cmdList_->Close();
	Execute();

	//フリップ
	swapchain_->Present(1, 0);
}

void WinApp::Execute()
{
	//コマンドリストの実行
	ID3D12CommandList* cmdlists[] = { cmdList_ };
	cmdQueue_->ExecuteCommandLists(1, cmdlists);
	cmdQueue_->Signal(_fence, ++_fenceVal);

	if (_fence->GetCompletedValue() != _fenceVal) {
		auto event = CreateEvent(nullptr, false, false, nullptr);
		_fence->SetEventOnCompletion(_fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	cmdAllocator_->Reset();//キューをクリア
	cmdList_->Reset(cmdAllocator_, nullptr);//再びコマンドリストをためる準備
}
#pragma once
#include<Windows.h>
#include<tchar.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<vector>
#include<string>
#include<assert.h>
#ifdef _DEBUG
#include<iostream>
#endif

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace std;

class WinApp
{
public:
	void DebugOutputFormatString(const char* format, ...);
	void EnableDebugLayer();
	void PreUpdate();
	void PostUpdate();
	void Execute();

	MSG msg;
	WinApp(const unsigned int WindowH, const unsigned int WindowW);
	~WinApp();

	/// <summary>
	/// îwåiêFÇÃê›íË
	/// </summary>
	/// <param name="r">red</param>
	/// <param name="g">green</param>
	/// <param name="b">blue</param>
	/// <param name="a">alfa</param>
	void SetBackColor(int r, int g, int b, float a);
	void SetWindowSize(const unsigned int winw, const unsigned int winh);
	int GetWinWidth() { return window_width; };
	int GetWinHeight() { return window_height; }
	ID3D12Device* GetDevice() { return dev_; }
	ID3D12GraphicsCommandList* cmdList_ = nullptr;
	WNDCLASSEX GetW() { return w; }
	HWND GetHwnd() { return hwnd; }
private:
	float clearColor[4];//êF
	unsigned int window_width = 1280;
	unsigned int window_height = 720;

	DXGI_SWAP_CHAIN_DESC swcDesc;
	vector<ID3D12Resource*> _backBuffers{ 2 };
	WNDCLASSEX w = { sizeof(WNDCLASSEX) };
	ID3D12Fence* _fence = nullptr;
	UINT64 _fenceVal = 0;

	ID3D12DescriptorHeap* rtvHeaps = nullptr;
	IDXGIFactory6* dxgiFactory_ = nullptr;
	ID3D12Device* dev_ = nullptr;
	ID3D12CommandAllocator* cmdAllocator_ = nullptr;
	ID3D12CommandQueue* cmdQueue_ = nullptr;
	IDXGISwapChain4* swapchain_ = nullptr;

	HWND hwnd;

};

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
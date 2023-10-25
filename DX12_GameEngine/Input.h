#pragma once
#include <d3dcompiler.h>
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class WinApp;
class Input
{
public:
	Input(WinApp* wp);
	~Input();
	//キーボード関連
	void KeybordInit();
	void keybordUpdate();

	BYTE key[256] = {};
private:
	HRESULT result = S_OK;
	WinApp* wp;
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;
};
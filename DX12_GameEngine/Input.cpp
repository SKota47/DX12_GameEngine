#include "Input.h"
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��

#include "WinApp.h"

Input::Input(WinApp* wp)
{
	this->wp = wp;
	// DirectInput�̏�����
	result = DirectInput8Create(
		this->wp->GetW().hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));
}

Input::~Input()
{
	// Release DirectInput resources
	if (keyboard) {
		keyboard->Unacquire();
		keyboard->Release();
	}
	if (directInput) {
		directInput->Release();
	}
}

void Input::KeybordInit()
{
	// �L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));
	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(
		wp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::keybordUpdate()
{
	// �L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();
	// �S�L�[�̓��͏�Ԃ��擾����
	keyboard->GetDeviceState(sizeof(key), key);
}

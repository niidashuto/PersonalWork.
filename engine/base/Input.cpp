#include "Input.h"
#include <cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
//������
void Input::Initialize(WinApp* winApp)
{
    this->winApp_ = winApp;
    HRESULT result;

    // DirectInput�̏�����
   
    result = DirectInput8Create(
        winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // �L�[�{�[�h�f�o�C�X�̐���
    
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));
    // ���̓f�[�^�`���̃Z�b�g
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
    assert(SUCCEEDED(result));
    // �r�����䃌�x���̃Z�b�g
    result = keyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
	
}
//�X�V
void Input::Update()
{
    //�O��̃L�[���͂�ێ�
    memcpy(keyPre, key, sizeof(key));

    // �L�[�{�[�h���̎擾�J�n
    keyboard->Acquire();
    
    keyboard->GetDeviceState(sizeof(key), key);
}
//�L�[�̉������`�F�b�N
bool Input::Pushkey(BYTE keyNumber) 
{
    //�w��L�[�������Ă����true��Ԃ�
    if (key[keyNumber]) 
    {
        return true;
    }
    return false;
}
//�L�[�̃g���K�[���`�F�b�N
bool Input::TriggerKey(BYTE keyNumber) 
{
    if (keyPre[keyNumber] == false && key[keyNumber])
    {
        return true;
    }
    return false;
}
#pragma once

#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION  0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

class Input
{
public:
	//namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public://�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
    /// <summary>
    /// �L�[�̉������`�F�b�N
    /// </summary>
    /// <param name="keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
    /// <returns>������Ă��邩</returns>
	bool Pushkey(BYTE keyNumber);
	/// <summary>
    /// �L�[�̃g���K�[���`�F�b�N
    /// </summary>
    /// <param name="keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
    /// <returns>�g���K�[��</returns>
	bool TriggerKey(BYTE keyNumber);

private: //�����o�ϐ�
	//�L�[�{�[�h�̃f�o�C�X
	ComPtr<IDirectInputDevice8> keyboard = nullptr;
	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput = nullptr;
	//�S�L�[�̏��
	BYTE key[256] = {};
	//�S�L�[�̏��
	BYTE keyPre[256] = {};
	//WindowsAPI
	WinApp* winApp_ = nullptr;

};

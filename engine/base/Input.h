#pragma once

#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION  0x0800 //DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"

class Input
{
public:
	//namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
    /// <summary>
    /// キーの押下をチェック
    /// </summary>
    /// <param name="keyNumber">キー番号(DIK_0 等)</param>
    /// <returns>押されているか</returns>
	bool Pushkey(BYTE keyNumber);
	/// <summary>
    /// キーのトリガーをチェック
    /// </summary>
    /// <param name="keyNumber">キー番号(DIK_0 等)</param>
    /// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber);

	static Input* GetInstance();

private: //メンバ変数
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard = nullptr;
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput = nullptr;
	//全キーの状態
	BYTE key[256] = {};
	//全キーの状態
	BYTE keyPre[256] = {};
	//WindowsAPI
	WinApp* winApp_ = nullptr;

};


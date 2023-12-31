#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>

struct ViewProjection
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public://構造体、バッファ
	struct ConstBufferDataViewProjection
	{
		XMMATRIX view;
		XMMATRIX projection;
		XMFLOAT3 cameraPos;
	};
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	//マッピング
	ConstBufferDataViewProjection* constMap_;

public://関数
	//初期化
	void Initialize();
	//定数バッファ生成
	void CreateConstBuffer();
	//マッピング
	void MapingCB();
	//更新
	void Update();

	//各行列更新
	void UpdateView();
	void UpdateProjection();

	//転送
	void Trans();

public://変数
	//視点
	XMFLOAT3 eye_;
	//注視点
	XMFLOAT3 target_;
	//上方向ベクトル
	XMFLOAT3 up_;

	//視野角
	float angle_ = 0.0f;
	//アスペクト比
	float aspect_ = 0.0f;
	//ニアクリップ(手前側の深度限界)
	float nearZ_ = 0.0f;
	//ファークリップ(奥側の深度限界)
	float farZ_ = 0.0f;

	//ビュー行列
	XMMATRIX matView_;
	//プロジェクション行列
	XMMATRIX matProjection_;
	//ビュープロジェクション行列(合成用)
	XMMATRIX matViewProjection_;
	//ビルボード行列
	XMMATRIX matBillboard_;
	//Y軸回りビルボード行列
	XMMATRIX matBillboardY_;

};
#pragma once
#include "Camera.h"
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include "PlayerBullet.h"
#include <DirectXMath.h>
#include <list>
#include <memory>
#include "Enemy.h"
#include "PostEffect.h"
#include "SpriteCommon.h"

class Player
{
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	~Player();

	//初期化
	void Initialize(Model* model, Object3d* obj, Input* input, Camera* camera);
	//リセット処理
	void Reset();

	//更新
	void Update();

	//プレイヤーの移動処理
	void Move();
	void CameraMove();

	//プレイヤーの攻撃処理
	void Attack();

	//転送
	void Trans();

	//ワールド座標を取得
	XMFLOAT3 GetWorldPosition();

	//描画
	void Draw();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	float easeInSine(float number) { return 1 - cosf((0.8f * 3.141592f) / 2); }

	

private:
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	//モデル
	Model* model_ = nullptr;
	Model* modelBullet_ = nullptr;

	Object3d* obj_ = nullptr;
	Object3d* objBullet_ = nullptr;
	//カメラ
	Camera* camera_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	Enemy* enemy_ = nullptr;

	PostEffect* postEffect_ = nullptr;

	SpriteCommon* spriteCommon_ = nullptr;

	//ポジション
	XMFLOAT3 pos;
	//アングル
	XMFLOAT3 angle;

	//死亡フラグとライフ
	bool isDead_ = false;
	int life_ = 5;

	const float rotLimitZ_ = 30.0f;
	const float rotLimitX_ = 30.0f;

	const float moveLimitX_ = 40.0f;
	const float moveLimitY_ = 40.0f;

	bool start_ = false;

	bool boss_ = false;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	bool IsBoss() const { return boss_; }
};

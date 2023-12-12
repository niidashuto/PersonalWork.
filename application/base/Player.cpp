#include "Player.h"
#include <cassert>
#include <imgui.h>


using namespace DirectX;

Player::~Player() {
	//モデルの解放

	delete modelBullet_;
	delete objBullet_;
}

void Player::Initialize(Model* model, Object3d* obj, Input* input, Camera* camera,Sprite* white, Sprite* gameover,Sprite* gameclear) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	camera_ = camera;
	obj_ = obj;
	//warning_ = warning;
	fadeIn_white = white;
	gameover_ = gameover;
	gameclear_ = gameclear;

	modelBullet_ = Model::LoadFromOBJ("playerbullet");
	objBullet_ = Object3d::Create();

	objBullet_->SetScale({ 5,5,5 });
	objBullet_->SetModel(modelBullet_);
	objBullet_->SetCamera(camera_);
	

	//シングルトンインスタンスを取得
	this->input_ = input;

	//ワールド変換の初期化
	pos = { 0.0f,20.0f,-60.0f };
	obj_->SetPosition(pos);

	//warning_->SetColor({ 1,1,1,warning_color });

	fadeIn_white->SetColor({ 1,1,1,fadein_color });

	gameover_->SetColor({ 1,1,1,gameover_color });

	gameclear_->SetColor({ 1,1,1,gamecler_color });

	Reset();

}

void Player::Reset() {
	
}
void Player::Update() {

	if (!dead_) {
		//死亡フラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

		//移動処理
		Move();
		CameraMove();
		//攻撃処理
		Attack();

		//弾更新
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { 
			bullet->Update();
		}

		//移動制限
		Trans();
	}

	obj_->Update();
}

void Player::Draw() {
	if (!dead_) {
		obj_->Draw();
		

		//弾描画
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Draw();
		}

	}
}

//移動処理
void Player::Move() {

	XMFLOAT3 move = obj_->GetPosition();
	XMFLOAT3 rot = obj_->GetRotation();
	XMFLOAT3 scale = obj_->GetScale();
	float moveSpeed = 1.0f;
	float rotSpeed = 1.0f;

	if (start_ == true&&!bossStart_&&!game_over_)
	{
		move.z-=2.0f;
		
		if (move.z <= -3500.0f)
		{
			bossStart_ = true;
			start_ = false;
			
			
		}
		
	}

	game_start_ = true;
	if (move.z <= -650.0f && !game_start_rot_)
	{
		//move.y = 55.0f;
		//move.x = -35.0f;
		game_start_rot_ = true;

	}
	if (game_start_rot_)
	{
		//move.y -= 0.5f;
		//move.x += 0.5f;
		if (move.x >= 0 && move.y <= 20.0f)
		{
			game_start_ = false;
			//game_start_rot_ = false;

		}
	}

	/*if (input_->Pushkey(DIK_7)) {

		if (gameclear_)
		{
			warning_color += 0.02f;
			warning_->SetColor({ 1,1,1,warning_color });
			if (gameclear_ && warning_color >= 1.0f)
			{
				clear_change_ = true;
			}
		}
	}*/

	//キーボード入力による移動処理
	XMMATRIX matTrans = XMMatrixIdentity();
	if (input_->Pushkey(DIK_A)) {
		move.x += moveSpeed;
		rot.z -= rotSpeed;
	}
	if (input_->Pushkey(DIK_D)) {
		move.x -= moveSpeed;
		rot.z += rotSpeed;
	}
	if (input_->Pushkey(DIK_W)) {
		move.y += moveSpeed;
		rot.x += rotSpeed;
	}
	if (input_->Pushkey(DIK_S)) {
		move.y -= moveSpeed;
		rot.x -= rotSpeed;
	}

	if (move.z<=-680.0f) {
		start_wait_timer -= 1.0f;
		if (start_wait_timer <= 0.0f)
		{
			start_ = true;
		}
	}

	/*if (input_->Pushkey(DIK_RETURN)&&!game_clear_)
	{
		title_ = false;
		transition_ = true;
		
	}*/
	
	//start_wait_timer -= 1.0f;
	

	//if (input_->Pushkey(DIK_3))
	//{
	//	//rot.y += 1.0f;
	//	scale.z += 0.5f;
	//	scale.x += 0.5f;
	//	scale.y -= 0.5f;

	//	
	//	scale.z = max(scale.z, 0);
	//	scale.z = min(scale.z, 10);

	//	scale.x = max(scale.x, 0);
	//	scale.x = min(scale.x, 10);

	//	scale.y = max(scale.y, 20);
	//	scale.y = min(scale.y, 10);
	//	
	//	//transition_2_ = true;
	//}
	/*if (warning_color >= 1.0f)
	{
		fadeIn_ = true;
		
	}*/

	/*if (fadein_color >= 1.0f)
	{
		fadeInWhite_ = true;

	}*/

	//if (fadeInWhite_)
	//{
	//	fadein_timer -= 1.0f;
	//	if (fadein_timer <= 0.0f)
	//	{
	//		transition_2_ = false;
	//		move.z = -680.0f;
	//		camera_->SetTarget({ 0,0,0.0f });
	//		camera_->SetEye({ 0,0,8.0f });
	//		camera_->SetUp({ 0,20,0 });
	//		camera_->CameraMoveVector({ 0,20,-620 });
	//		//rot.y = 0;
	//		

	//	}
	//	fadein_color -= 0.02f;
	//	fadeIn_white->SetColor({ 1,1,1,fadein_color });
	//	if (fadein_color <= 0)
	//	{
	//		fadein_timer = 60.0f * 3;

	//	}

	//}

	if (game_over_)
	{
		game_over_timer -= 1.0f;
		if (game_over_timer <= 0)
		{
			rot.y += 5.0f;
			scale.x -= 0.1f;
			scale.y -= 0.1f;
			scale.z -= 0.1f;
			if (scale.x <= 0)
			{
				extinction_timer -= 1.0f;
				scale.x += 0.1f;
				scale.y += 0.1f;
				scale.z += 0.1f;
				player_extinction_ = true;
				dead_ = true;
				if (extinction_timer <= 0)
				{
					player_extinction_ = false;
					//gameover_color += 0.02f;
					//gameover_->SetColor({ 1,1,1,gameover_color });
					
					
				}
				
			}
		}
	}

	/*if (game_clear_)
	{
		game_clear_timer -= 1.0f;
		if (game_clear_timer <= 0)
		{
			dead_ = true;
			gamecler_color += 0.02f;
			gameclear_->SetColor({ 1,1,1,gamecler_color });
			if (gamecler_color >= 1.0f)
			{
				clear_change_ = true;
			}
		}
		
	}*/

	/*if (transition_) {
		warning_color += 0.02f;
		warning_->SetColor({ 1,1,1,warning_color });
	}*/

	/*if (transition_2_) {
		scale.z -= 0.5f;
		scale.x -= 0.5f;
		scale.y += 0.5f;
		if (scale.z <= 0)
		{
			scale.z = max(scale.z, 0);
			scale.z = min(scale.z, 0);

			scale.x = max(scale.x, 0);
			scale.x = min(scale.x, 0);

			scale.y = max(scale.y, 10);
			scale.y = min(scale.y, 10);
		}
		fadein_color += 0.02f;
		fadeIn_white->SetColor({ 1,1,1,fadein_color });
	}*/

	//自機の回転(Z軸)
	if (!input_->Pushkey(DIK_A)&& !input_->Pushkey(DIK_D))
	{
		if (rot.z < 0)
		{
			rot.z += rotSpeed;
		}
		else if (rot.z > 0)
		{
			rot.z -= rotSpeed;
		}
	}

	//自機の回転(X軸)
	if (!input_->Pushkey(DIK_W) && !input_->Pushkey(DIK_S))
	{
		if (rot.x < 0)
		{
			rot.x += rotSpeed;
		}
		else if (rot.x > 0)
		{
			rot.x -= rotSpeed;
		}
	}

	//回転制限
	
	rot.z = max(rot.z, -kRotLimitZ_);
	rot.z = min(rot.z, +kRotLimitZ_);

	rot.x = max(rot.x, -kRotLimitX_);
	rot.x = min(rot.x, +kRotLimitX_);

	//移動制限
	move.x = max(move.x, -kMoveLimitX_);
	move.x = min(move.x, +kMoveLimitX_);

	move.y = max(move.y, 0.0f);
	move.y = min(move.y, +kMoveLimitY_);
	

	obj_->SetPosition(move);
	obj_->SetRotation(rot);
	obj_->SetScale(scale);
}

void Player::CameraMove()
{
	//XMFLOAT3 move = obj_->GetPosition();
	XMFLOAT3 cmove = camera_->GetEye();
	XMFLOAT3 tmove = camera_->GetTarget();
	float moveSpeed = 1.0f;
	
	if (start_ == true&&!bossStart_&&!game_over_)
	{
		cmove.z-=2.0f;
		tmove.z-=2.0f;
	}
	
	//キーボード入力による移動処理
	XMMATRIX matTrans = XMMatrixIdentity();
	if (input_->Pushkey(DIK_LEFT)) {
		//move.x -= moveSpeed;
		cmove.x -= moveSpeed;
		tmove.x -= moveSpeed;
	}
	if (input_->Pushkey(DIK_RIGHT)) {
		//move.x += moveSpeed;
		cmove.x += moveSpeed;
		tmove.x += moveSpeed;
	}
	if (input_->Pushkey(DIK_UP)) {
		//move.y += moveSpeed;
		cmove.y += moveSpeed;
		tmove.y += moveSpeed;
	}
	if (input_->Pushkey(DIK_DOWN)) {
		//move.y -= moveSpeed;
		cmove.z+= moveSpeed;
		tmove.z+= moveSpeed;
	}

	
	
	
	//obj_->SetPosition(move);
	camera_->SetEye(cmove);
	camera_->SetTarget(tmove);
}

//攻撃処理
void Player::Attack() {
	
		if (input_->TriggerKey(DIK_SPACE)) {
			//弾の速度
			const float kBulletSpeed = 4.0f;
			XMFLOAT3 velocity(0.0f, 0.0f, -kBulletSpeed);



			XMMATRIX matVec = XMMatrixIdentity();
			matVec.r[0].m128_f32[0] = velocity.x;
			matVec.r[0].m128_f32[1] = velocity.y;
			matVec.r[0].m128_f32[2] = velocity.z;
			matVec.r[0].m128_f32[3] = 0.0f;

			matVec *= obj_->GetWorld();

			//自キャラの座標をコピー
			XMFLOAT3 position = obj_->GetPosition();

			//弾を生成し初期化
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//PlayerBullet* newBullet=new PlayerBullet();

			newBullet->Initialize(modelBullet_, objBullet_, position, velocity);

			//弾を登録
			bullets_.push_back(std::move(newBullet));
			//あるメモリの所有権を持つunique_ptrはただ一つしか存在できない
			//その所有権を謙渡するための機能が std::move()
		}
	
}

void Player::Trans() {

	XMMATRIX world;
	//行列更新
	world = XMMatrixIdentity();
	XMMATRIX matWorld = XMMatrixIdentity();

	XMMATRIX matScale = XMMatrixScaling(obj_->GetScale().x, obj_->GetScale().y, obj_->GetScale().z);

	XMMATRIX matRot = XMMatrixRotationZ(obj_->GetRotation().z)
		* XMMatrixRotationX(obj_->GetRotation().x) * XMMatrixRotationY(obj_->GetRotation().y);

	XMMATRIX matTrans = XMMatrixTranslation(obj_->GetPosition().x,
		obj_->GetPosition().y, obj_->GetPosition().z);

	//合成
	matWorld = matScale * matRot * matTrans;

	world = matWorld;
	obj_->SetWorld(world);

}

void Player::Warning()
{
	
}

//ワールド座標を取得
XMFLOAT3 Player::GetWorldPosition() {

	//ワールド座標を取得
	XMFLOAT3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = obj_->GetPosition().x;
	worldPos.y = obj_->GetPosition().y;
	worldPos.z = obj_->GetPosition().z;

	return worldPos;
}

//衝突を検出したら呼び出されるコールバック関数
void Player::OnCollision() {
	life_--;

	
	
	if (life_ <= 0) {
		game_over_ = true;
		start_ = false;
		
		//dead_ = true;
	}
}

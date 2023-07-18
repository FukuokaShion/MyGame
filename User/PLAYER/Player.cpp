#include "Player.h"
#include "FbxLoader.h"
#include"PlayerStandby.h"

Player::Player() {
	//モデル生成
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->PlayAnimation();
	hp = new PlayerHp;

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 5.0f;

	attackHitBox.center = { 0,0,0 };
	attackHitBox.radius = 1.0f;
}

Player::~Player() {
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Initialize(Input* input) {
	input_ = input;
	hp->Initialize();
	action = new PlayerAction(new PlayerStandby, input);
	action->SetTransform(&fbxObject3d_->wtf);
}

void Player::Update() {
	action->Update();
	bodyHitBox.center = fbxObject3d_->wtf.position;

	Move();
	Rota();
	CamRota();

	camera_->Update();

	fbxObject3d_->Update();
}

void Player::Move() {
	//移動量
	Vector3 velocity = { 0,0,0 };
	//移動速度
	float speed = 0.5f;

	//スティック入力方向取得
	Vector2 stickVec = input_->GetLeftStickVec();
	//移動方向に変換
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//単位ベクトル化
	velocity = velocity.nomalize();
	//移動ベクトルに変換
	velocity *= speed;

	//キーボード入力
	if (input_->PushKey(DIK_A)) {
		velocity.x = -speed;
	}else if (input_->PushKey(DIK_D)) {
		velocity.x = speed;
	}
	if (input_->PushKey(DIK_W)) {
		velocity.z = speed;
	}else if (input_->PushKey(DIK_S)) {
		velocity.z = -speed;
	}

	//カメラが向いている方向に合わせる
	velocity = Matrix4::bVelocity(velocity,camera_->wtf.matWorld);

	fbxObject3d_->wtf.position += velocity;
}

void Player::Rota() {
	if (input_->LeftStickInput()) {
		Vector2 stickVec = input_->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
	
		fbxObject3d_->wtf.rotation.y = theta + camera_->wtf.rotation.y;
	}
}

void Player::CamRota() {
	//左右
	Vector3 theta;

	float PI = 3.1415f;
	Vector2 camRotaSpeed = { PI / 1800.0f, PI / 1800.0f };
	float sensitivity = 10.0f;

	if (input_->StickInput(R_LEFT)) {
		theta.y = camRotaSpeed.y * sensitivity;
	}
	else if (input_->StickInput(R_RIGHT)) {
		theta.y = -camRotaSpeed.y * sensitivity;
	}

	if (input_->StickInput(R_UP)) {
		theta.x = camRotaSpeed.x * sensitivity;
	}
	else if (input_->StickInput(R_DOWN)) {
		theta.x = -camRotaSpeed.x * sensitivity;
	}

	camera_->wtf.rotation += theta;
}

void Player::OnCollision(int damage) {
	hp->Damage(damage);
}

void Player::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
}
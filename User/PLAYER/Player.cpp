/**
 * @file Player.cpp
 * @brief プレイヤー本体
 */

#include "Player.h"
#include "FbxLoader.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

Player::Player() {
	//モデル生成
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	hp = new PlayerHp;

	state_->SetPlayer(this);
}

Player::~Player() {
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Initialize() {
	input_ = Input::GetInstance();

	//サウンド
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("col.wav");
	audio->LoadWave("jump.wav");
	audio->LoadWave("landing.wav");
	audio->LoadWave("attack.wav");
	audio->LoadWave("jumpAttack.wav");
	audio->LoadWave("avoid.wav");
	audio->LoadWave("run.wav");

	hp->Initialize();
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.scale = { 0.8f,0.8f,0.8f };

	gaugeLimit = 60;

	TransitionTo(new PlayerStandby);

	body = new BaseCollider;
	body->SetAttribute(Attribute::PlyerBody);
	CollisionManager::GetInstance()->AddCollider(body);
}

void Player::Update() {
	state_->Update();

	CamRota();
	fbxObject3d_->wtf.UpdateMat();
	body->SetCenter(fbxObject3d_->wtf.position);
	camera_->Update();
	fbxObject3d_->Update();

	OnCollision();

	if (gaugeTimer < 0) {
		if (damageGauge > hp->GetHp()) {
			damageGauge--;
		}
	}
	else {
		gaugeTimer--;
	}

	//uint32_t sowrdNum = 34;
	//skydome->wtf.position = fbxObject3d_->GetBonWorldPos(sowrdNum);
}

void Player::CamRota() {
	//左右
	Vector3 theta = { 0,0,0 };

	float PI = 3.1415f;
	Vector2 camRotaSpeed = { PI / 1800.0f, PI / 1800.0f };
	float sensitivity = 10.0f;

	if (input_->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed.y * sensitivity;
	}
	else if (input_->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed.y * sensitivity;
	}

	if (input_->StickInput(R_DOWN)) {
		theta.x = camRotaSpeed.x * sensitivity;
	}
	else if (input_->StickInput(R_UP)) {
		theta.x = -camRotaSpeed.x * sensitivity;
	}

	camera_->wtf.rotation += theta;
}

void Player::OnCollision() {
	if (body->GetIsHit().enemyAttack || body->GetIsHit().enemyBullet) {
		PlayWav("col.wav");
		hp->Damage(10);
		gaugeTimer = gaugeLimit;
		damageGauge = hp->GetOldHp();
	}
}

void Player::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
}

//状態を変更する
void Player::TransitionTo(PlayerState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
}

void Player::PlayWav(const std::string& filename) {
	if (filename == "col.wav") {
		pSourceVoice[0] = audio->PlayWave("col.wav");
	}
	else if (filename == "jump.wav") {
		pSourceVoice[1] = audio->PlayWave("jump.wav");
	}
	else if (filename == "landing.wav") {
		pSourceVoice[2] = audio->PlayWave("landing.wav");
	}
	else if (filename == "attack.wav") {
		pSourceVoice[3] = audio->PlayWave("attack.wav");
	}
	else if (filename == "jumpAttack.wav") {
		pSourceVoice[4] = audio->PlayWave("jumpAttack.wav");
	}
	else if (filename == "avoid.wav") {
		pSourceVoice[5] = audio->PlayWave("avoid.wav");
	}
	else if (filename == "run.wav") {
		pSourceVoice[6] = audio->PlayWave("run.wav");
	}
}

void Player::StopWav() {
	audio->StopWave(pSourceVoice[6]);
}

void Player::Move(Vector3 velocity) {
	//新しい座標
	Vector3 newPos = fbxObject3d_->wtf.position + velocity;

	//中心からの距離
	float distance = sqrt((newPos.x * newPos.x) + (newPos.z * newPos.z));

	int limit = 49;

	//範囲外なら
	if (distance > limit) {
		//角度
		float theta = atan2f(newPos.z, newPos.x);

		Vector3 limitPos = { limit * cosf(theta),newPos.y ,limit * sinf(theta) };

		newPos = limitPos;
	}

	fbxObject3d_->wtf.position = newPos;
};
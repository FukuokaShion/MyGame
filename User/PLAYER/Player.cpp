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

void Player::Initialize(Input* input) {
	input_ = input;
	state_->SetInput(input_);

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

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 3.0f;
	bodyHitBox.radius = 1.0f;

	gaugeLimit = 60;

	attackHitBox.center = { 0,0,0 };
	attackHitBox.radius = 1.0f;

	TransitionTo(new PlayerStandby);
}

void Player::Update() {
	state_->Update();

	bodyHitBox.center = fbxObject3d_->wtf.position;
	fbxObject3d_->wtf.position += CollisionManager::Body2Body();
	CamRota();

	camera_->Update();
	fbxObject3d_->Update();

	if (gaugeTimer < 0) {
		if (damageGauge > hp->GetHp()) {
			damageGauge--;
		}
	}else {
		gaugeTimer--;
	}
}

void Player::CamRota() {
	//左右
	Vector3 theta;

	float PI = 3.1415f;
	Vector2 camRotaSpeed = { PI / 1800.0f, PI / 1800.0f };
	float sensitivity = 10.0f;

	if (input_->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed.y * sensitivity;
	}
	else if (input_->StickInput(R_LEFT)) {
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
	PlayWav("col.wav");
	hp->Damage(damage);
	gaugeTimer = gaugeLimit;
	damageGauge = hp->GetOldHp();
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
	}else if (filename == "jump.wav") {
		pSourceVoice[1] = audio->PlayWave("jump.wav");
	}else if (filename == "landing.wav") {
		pSourceVoice[2] = audio->PlayWave("landing.wav");
	}else if (filename == "attack.wav") {
		pSourceVoice[3] = audio->PlayWave("attack.wav");
	}else if (filename == "jumpAttack.wav") {
		pSourceVoice[4] = audio->PlayWave("jumpAttack.wav");
	}else if (filename == "avoid.wav") {
		pSourceVoice[5] = audio->PlayWave("avoid.wav");
	}else if (filename == "run.wav") {
		pSourceVoice[6] = audio->PlayWave("run.wav");
	}
}

void Player::StopWav() {
	 audio->StopWave(pSourceVoice[6]);
}
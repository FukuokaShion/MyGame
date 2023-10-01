#include "Player.h"
#include "FbxLoader.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

Player::Player() {
	//���f������
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

	//�T�E���h
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

	Move(CollisionManager::Body2Body());
	CamRota();
	fbxObject3d_->wtf.UpdateMat();
	camera_->Update();
	fbxObject3d_->Update();

	if (gaugeTimer < 0) {
		if (damageGauge > hp->GetHp()) {
			damageGauge--;
		}
	}else {
		gaugeTimer--;
	}

	//uint32_t sowrdNum = 34;
	//skydome->wtf.position = fbxObject3d_->GetBonWorldPos(sowrdNum);
}

void Player::CamRota() {
	//���E
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

//��Ԃ�ύX����
void Player::TransitionTo(PlayerState* state) {
	//�폜
	delete state_;
	//�V�K�쐬
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

void Player::Move(Vector3 velocity) {
	//�V�������W
	Vector3 newPos = fbxObject3d_->wtf.position + velocity;
	
	//���S����̋���
	float distance = sqrt((newPos.x * newPos.x) + (newPos.z * newPos.z));

	int limit = 49;

	//�͈͊O�Ȃ�
	if (distance > limit) {
		//�p�x
		float theta = atan2f(newPos.z, newPos.x);

		Vector3 limitPos = { limit * cosf(theta),newPos.y ,limit* sinf(theta) };

		newPos = limitPos;
	}

	fbxObject3d_->wtf.position = newPos;
};
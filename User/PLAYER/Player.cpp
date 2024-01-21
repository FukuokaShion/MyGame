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
	hp_ = new PlayerHp;

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

	hp_->Initialize();
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.scale = { 0.8f,0.8f,0.8f };

	gaugeLimit_ = 60;

	TransitionTo(new PlayerStandby);

	ui_.Initialize();

	boneNum[0] = 0;
	boneNum[1] = 0;
	boneNum[2] = 5;
	boneNum[3] = 9;
	boneNum[4] = 33;

	for (int i = 0; i < maxColliderNum; i++) {
		colliders_[i] = new BaseCollider;
		colliders_[i]->SetAttribute(Attribute::PlyerBody);
		colliders_[i]->SetRad(rad_);
		CollisionManager::GetInstance()->AddCollider(colliders_[i]);
	}
	isRockOn_ = false;
}

void Player::Update() {
	state_->Update();

	if (Input::GetInstance()->PButtonTrigger(RSTICK)) {
		if (isRockOn_) {
			isRockOn_ = false;
		}else {
			isRockOn_ = true;
		}
	}

	fbxObject3d_->wtf.UpdateMat();
	fbxObject3d_->Update();

	OnCollision();

	if (gaugeTimer_ < 0) {
		if (damageGauge_ > hp_->GetHp()) {
			damageGauge_ -= 10;
		}
	}else {
		gaugeTimer_--;
	}

	ui_.Update(GetDamage(), GetHp());

	colliders_[0]->SetCenter(fbxObject3d_->wtf.position + Vector3{ 0,rad_,0 });
	for (int i = 1; i < maxColliderNum; i++) {
		colliders_[i]->SetCenter(fbxObject3d_->GetBonWorldPos(boneNum[i]));
	}
}

void Player::OnCollision() {
	for (int i = 0; i < maxColliderNum; i++) {
		if (isInvincible_ == false) {
			if (colliders_[i]->GetIsHit().enemyAttack == true) {
				PlayWav("col.wav");
				hp_->Damage(colliders_[i]->GetDamage());
				gaugeTimer_ = gaugeLimit_;
				damageGauge_ = hp_->GetOldHp();
			}else if (colliders_[i]->GetIsHit().enemyBullet == true) {
				PlayWav("col.wav");
				hp_->Damage(colliders_[i]->GetDamage());
				gaugeTimer_ = gaugeLimit_;
				damageGauge_ = hp_->GetOldHp();
			}
		}
		colliders_[i]->RemoveHit(Attribute::EnemyAttack);
		colliders_[i]->RemoveHit(Attribute::EnemyBullet);
	}
}

void Player::Draw() {
	if (hp_->IsLive()) {
		fbxObject3d_->Draw();
	}
}

void Player::DrawSprite() {
	ui_.Draw();
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
		pSourceVoice_[0] = audio->PlayWave("col.wav");
	}
	else if (filename == "jump.wav") {
		pSourceVoice_[1] = audio->PlayWave("jump.wav");
	}
	else if (filename == "landing.wav") {
		pSourceVoice_[2] = audio->PlayWave("landing.wav");
	}
	else if (filename == "attack.wav") {
		pSourceVoice_[3] = audio->PlayWave("attack.wav");
	}
	else if (filename == "jumpAttack.wav") {
		pSourceVoice_[4] = audio->PlayWave("jumpAttack.wav");
	}
	else if (filename == "avoid.wav") {
		pSourceVoice_[5] = audio->PlayWave("avoid.wav");
	}
	else if (filename == "run.wav") {
		pSourceVoice_[6] = audio->PlayWave("run.wav");
	}
}

void Player::StopWav() {
	audio->StopWave(pSourceVoice_[6]);
}

void Player::Move(Vector3 velocity) {
	//新しい座標
	Vector3 newPos = fbxObject3d_->wtf.position + velocity;

	//中心からの距離
	float distance = sqrt((newPos.x * newPos.x) + (newPos.z * newPos.z));

	const int limit = 49;

	//範囲外なら
	if (distance > limit) {
		//角度
		float theta = atan2f(newPos.z, newPos.x);

		Vector3 limitPos = { limit * cosf(theta),newPos.y ,limit * sinf(theta) };

		newPos = limitPos;
	}

	fbxObject3d_->wtf.position = newPos;
};


bool Player::Damage(int damage) {
	if (isInvincible_ == false) {
		if (fbxObject3d_->wtf.position.y < 0.5f) {
			hp_->Damage(damage);
			return true;
		}
	}
	return false;
};
/**
 * @file Enemy.cpp
 * @brief 敵クラス本体
 */

#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyShooting.h"

Enemy::Enemy() {
	//モデル生成
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemy");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);

	hp_ = new EnemyHp();

	isAttack_ = false;
	power_ = 0;

	state_->SetEnemy(this);

	particle_ = new EnemyParticle;
}

void Enemy::Initialize() {
	//サウンド
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("fire.wav");
	audio_->LoadWave("enemyat.wav");

	TransitionTo(new Standby);
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.position = { 0,0,8 };
	hp_->Initialize();

	isAttack_ = false;
	power_ = 0;
	EnemyBullet::StaticInitialize();

	body_ = new BaseCollider;
	body_->SetAttribute(Attribute::EnemyBody);
	body_->SetRad(1.3f);
	CollisionManager::GetInstance()->AddCollider(body_);
	body2_ = new BaseCollider;
	body2_->SetAttribute(Attribute::EnemyBody);
	body2_->SetRad(1.0f);
	CollisionManager::GetInstance()->AddCollider(body2_);
	body3_ = new BaseCollider;
	body3_->SetAttribute(Attribute::EnemyBody);
	body3_->SetRad(1.0f);
	CollisionManager::GetInstance()->AddCollider(body3_);
	body4_ = new BaseCollider;
	body4_->SetAttribute(Attribute::EnemyBody);
	body4_->SetRad(1.0f);
	CollisionManager::GetInstance()->AddCollider(body4_);
	body5_ = new BaseCollider;
	body5_->SetAttribute(Attribute::EnemyBody);
	body5_->SetRad(1.0f);
	CollisionManager::GetInstance()->AddCollider(body5_);

	num[0] = 1;
	num[1] = 4;
	num[2] = 7;
	num[3] = 12;
	num[4] = 17;
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp_;
	delete state_;
	delete particle_;
	bullets_.clear();
	EnemyBullet::StaticFinalize();
}

void Enemy::Update(Vector3 playerPos) {
	if (hp_->IsLive()) {
		//当たり判定
		body_->SetCenter(fbxObject3d_->wtf.position);
		OnCollision();

		//行動
		state_->Update(playerPos);

		//オブジェクト
		fbxObject3d_->Update();

		//弾
		bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
		for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
			bullet->Update();
		}
	}
	//パーティクル
	particle_->Update();


	body_->SetCenter(fbxObject3d_->GetBonWorldPos(num[0]));
	body2_->SetCenter(fbxObject3d_->GetBonWorldPos(num[1]));
	body3_->SetCenter(fbxObject3d_->GetBonWorldPos(num[2]));
	body4_->SetCenter(fbxObject3d_->GetBonWorldPos(num[3]));
	body5_->SetCenter(fbxObject3d_->GetBonWorldPos(num[4]));
}

void Enemy::OnCollision() {
	if (body_->GetIsHit().playerAttack) {
		hp_->Damage(10);
		body_->RemoveHit(Attribute::PlayerAttack);
		particle_->OnColision(body_->GetHitPos().playerAttack);
	}
	
	if (body2_->GetIsHit().playerAttack) {
		hp_->Damage(10);
		body2_->RemoveHit(Attribute::PlayerAttack);
		particle_->OnColision(body_->GetHitPos().playerAttack);
	}

	if (body3_->GetIsHit().playerAttack) {
		hp_->Damage(10);
		body3_->RemoveHit(Attribute::PlayerAttack);
		particle_->OnColision(body_->GetHitPos().playerAttack);
	}

	if (body4_->GetIsHit().playerAttack) {
		hp_->Damage(10);
		body4_->RemoveHit(Attribute::PlayerAttack);
		particle_->OnColision(body_->GetHitPos().playerAttack);
	}

	if (body5_->GetIsHit().playerAttack) {
		hp_->Damage(10);
		body5_->RemoveHit(Attribute::PlayerAttack);
		particle_->OnColision(body_->GetHitPos().playerAttack);
	}
}

void Enemy::Draw() {
	if (hp_->IsLive()) {
		fbxObject3d_->Draw();
	}
}

void Enemy::ObjDraw() {
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw();
	}
	particle_->Draw();
}

void Enemy::CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos, velocity, liveLimit, stayTime);
	bullets_.push_back(std::move(newBullet));
}

//状態を変更する
void Enemy::TransitionTo(EnemyState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
}

void Enemy::PlayWave(const std::string& filename) {
	if (filename == "fire.wav") {
		pSourceVoice_[0] = audio_->PlayWave("fire.wav");
	}
	else if (filename == "enemyat.wav") {
		pSourceVoice_[1] = audio_->PlayWave("enemyat.wav");
	}
}

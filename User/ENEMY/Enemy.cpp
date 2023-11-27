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
	deatgparticle_ = new EnemyDeathParticle;
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

	DeathTimer = 0;

	ui_.Initialize();

	boneNum_[0] = SPINE1;
	boneNum_[1] = SPINE2;
	boneNum_[2] = HEAD;
	boneNum_[3] = HAND_R;
	boneNum_[4] = HAND_L;
	boneNum_[5] = ARM1_R;
	boneNum_[6] = ARM2_R;
	boneNum_[7] = ARM1_L;
	boneNum_[8] = ARM2_L;
	boneNum_[9] = LEG_R;
	boneNum_[10] = LEG_L;

	for (int i = 0; i < MaxColliderNum; i++) {
		colliders_[i] = new BaseCollider;
		colliders_[i]->SetAttribute(Attribute::EnemyBody);
		CollisionManager::GetInstance()->AddCollider(colliders_[i]);
	}

	colliders_[0]->SetRad(0.7f);
	colliders_[1]->SetRad(0.7f);
	colliders_[2]->SetRad(0.5f);
	colliders_[3]->SetRad(0.3f);
	colliders_[4]->SetRad(0.3f);
	colliders_[5]->SetRad(0.3f);
	colliders_[6]->SetRad(0.3f);
	colliders_[7]->SetRad(0.3f);
	colliders_[8]->SetRad(0.3f);
	colliders_[9]->SetRad(0.6f);
	colliders_[10]->SetRad(0.6f);
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp_;
	delete state_;
	delete particle_;
	delete deatgparticle_;
	bullets_.clear();
	EnemyBullet::StaticFinalize();
}

void Enemy::Update(Vector3 playerPos) {
	if (hp_->IsLive()) {
		//オブジェクト
		fbxObject3d_->Update();

		//当たり判定
		for (int i = 0; i < MaxColliderNum; i++) {
			colliders_[i]->SetCenter(fbxObject3d_->GetBonWorldPos(boneNum_[i]));
		}
		OnCollision();

		//行動
		state_->Update(playerPos);

		
	}else {
		DeathTimer++;
		if (DeathTimer < DeathLimit) {
			deatgparticle_->Accrual(fbxObject3d_->wtf.position);
		}
	}
	//パーティクル
	particle_->Update();
	deatgparticle_->Update();
	//弾
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//ui
	ui_.Update(GetHp());
}

void Enemy::OnCollision() {
	for (int i = 0; i < MaxColliderNum; i++) {
		if (colliders_[i]->GetIsHit().playerAttack) {
			hp_->Damage(colliders_[i]->GetDamage());
			particle_->OnColision(colliders_[i]->GetHitPos().playerAttack);
			colliders_[i]->RemoveHit(Attribute::PlayerAttack);
		}
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
	deatgparticle_->Draw();
}

void Enemy::SpriteDraw() {
	ui_.Draw();
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

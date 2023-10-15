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

	hp = new EnemyHp();

	isAttack_ = false;
	power_ = 0;

	state_->SetEnemy(this);

	particle = new EnemyParticle;
}

void Enemy::Initialize() {
	//サウンド
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("fire.wav");
	audio->LoadWave("enemyat.wav");

	TransitionTo(new Standby);
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.position = { 0,0,8 };
	hp->Initialize();

	isAttack_ = false;
	power_ = 0;
	EnemyBullet::StaticInitialize();

	body = new BaseCollider;
	body->SetAttribute(Attribute::EnemyBody);
	CollisionManager::GetInstance()->AddCollider(body);
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp;
	delete state_;
	delete particle;
	bullets.clear();
	EnemyBullet::StaticFinalize();
}

void Enemy::Update(Vector3 playerPos) {
	if (hp->IsLive()) {
		//当たり判定
		body->SetCenter(fbxObject3d_->wtf.position);
		OnCollision();

		//行動
		state_->Update(playerPos);

		//オブジェクト
		fbxObject3d_->Update();

		//弾
		bullets.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
		for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
			bullet->Update();
		}
	}
	//パーティクル
	particle->Update();
}

void Enemy::OnCollision() {
	if (body->GetIsHit().playerAttack) {
		hp->Damage(10);
		particle->OnColision(body->GetHitPos().playerAttack);
	}
}

void Enemy::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
}

void Enemy::ObjDraw() {
	for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
		bullet->Draw();
	}
	particle->Draw();
}

void Enemy::CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos, velocity, liveLimit, stayTime);
	bullets.push_back(std::move(newBullet));
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
		pSourceVoice[0] = audio->PlayWave("fire.wav");
	}
	else if (filename == "enemyat.wav") {
		pSourceVoice[1] = audio->PlayWave("enemyat.wav");
	}
}

/**
 * @file EnemyShootingParticle.cpp
 * @brief 敵のヒット時エフェクト
 */

#include"EnemyShootingParticle.h"

EnemyShootingParticle::EnemyShootingParticle() {
	//パーティクル生成
	shootingParticle_ = std::make_unique<ParticleManager>();
	shootingParticle_.get()->Initialize();
	shootingParticle_->LoadTexture("bulletCreate.png");
}

EnemyShootingParticle::~EnemyShootingParticle() {
}

void EnemyShootingParticle::Create(Vector3 createPos) {
	for (int i = 0; i < 5; i++) {
		const float half = 0.5f;

		Vector3 pos = createPos;

		//速度
		const float rnd_vel = 0.02f;
		Vector3 vel = { 0,0,0 };
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel * half;

		//加速度
		const float rnd_acc = 0.00001f;
		Vector3 acc = { 0,0,0 };
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc * half;

		//パーティクルサイズ
		const float start = 0.1f;
		const float end = 0.0f;

		//生存時間
		const int lifeTime = 40;

		//追加
		shootingParticle_->Add(lifeTime, pos, vel, acc, start, end);
	}
}

void EnemyShootingParticle::Update() {
	shootingParticle_->Update();
}

void EnemyShootingParticle::Draw() {
	shootingParticle_->Draw();
}
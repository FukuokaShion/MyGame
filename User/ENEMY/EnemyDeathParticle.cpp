/**
 * @file EnemyDeathParticle.cpp
 * @brief 敵の死亡時エフェクト
 */

#include"EnemyDeathParticle.h"

EnemyDeathParticle::EnemyDeathParticle() {
	//パーティクル生成
	particle_ = std::make_unique<ParticleManager>();
	particle_.get()->Initialize();
	particle_->LoadTexture("deathParticle.png");
}

EnemyDeathParticle::~EnemyDeathParticle() {
}

void EnemyDeathParticle::Accrual(Vector3 centerPos) {
	for (int i = 0; i < 10; i++) {
		//生成位置
		const float rnd_pos = 3.0f;
		Vector3 pos = centerPos;

		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * 4.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//速度
		Vector3 vel = { 0,0,0 };
		vel.x = (float)rand() / RAND_MAX * 0.02f - 0.02f / 2.0f;
		vel.y = (float)rand() / RAND_MAX * 0.02f - 0.02f / 2.0f;
		vel.z = (float)rand() / RAND_MAX * 0.05f;

		//加速度
		Vector3 acc = { 0,0,0 };

		//追加
		particle_->Add(90, pos, vel, acc, 0.1f, 0.0f);
	}
}

void EnemyDeathParticle::Update() {
	particle_->Update();
}

void EnemyDeathParticle::Draw() {
	particle_->Draw();
}
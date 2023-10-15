/**
 * EnemyParticle.cpp
 * 敵のヒット時エフェクト
 */

#include"EnemyParticle.h"

EnemyParticle::EnemyParticle() {
	//パーティクル生成
	DamageParticle = std::make_unique<ParticleManager>();
	DamageParticle.get()->Initialize();
	DamageParticle->LoadTexture("blod.png");
}

EnemyParticle::~EnemyParticle() {
}

void EnemyParticle::OnColision(Vector3 hitPos) {
	for (int i = 0; i < 20; i++) {
		const float rnd_pos = 0.3f;
		Vector3 pos = hitPos;
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//速度
		const float rnd_vel = 0.1f;
		Vector3 vel = { 0,0,0 };
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		//加速度
		const float rnd_acc = 0.00001f;
		Vector3 acc = { 0,0,0 };
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		DamageParticle->Add(30, pos, vel, acc, 0.3f, 0.0f);
	}
}

void EnemyParticle::Update() {
	DamageParticle->Update();
}

void EnemyParticle::Draw() {
	DamageParticle->Draw();
}
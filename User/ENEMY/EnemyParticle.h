#pragma once
#include "ParticleManager.h"

class EnemyParticle {
public:
	EnemyParticle();
	~EnemyParticle();

	void OnColision(Vector3 hitPos);

	void Update();

	void Draw();

public:
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> DamageParticle;
};
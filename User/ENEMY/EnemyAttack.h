#pragma once
#include"EnemyState.h"

//�U��
class EnemyAttack : public EnemyState {
public:
	EnemyAttack();

	void Update() override;
};
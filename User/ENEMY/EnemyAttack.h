#pragma once
#include"EnemyState.h"

//���1�̃N���X
class EnemyAttack : public EnemyState {
public:
	void Update(Transform* wtf) override;
};
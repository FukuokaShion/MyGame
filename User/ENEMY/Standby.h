#pragma once
#include"EnemyState.h"

//���1�̃N���X
class Standby : public EnemyState {
public:
	void Update(Transform* wtf) override;
};
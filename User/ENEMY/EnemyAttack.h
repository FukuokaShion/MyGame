#pragma once
#include"EnemyState.h"

//状態1のクラス
class EnemyAttack : public EnemyState {
public:
	void Update(Transform* wtf) override;
};
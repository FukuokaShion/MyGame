#pragma once
#include"EnemyState.h"

//UŒ‚
class EnemyAttack : public EnemyState {
public:
	EnemyAttack();

	void Update() override;

private:
	const int limit = 40;
	int timer = limit;

};
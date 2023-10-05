#pragma once
#include"EnemyState.h"

//射撃
class EnemyRoundShooting : public EnemyState {
public:
	EnemyRoundShooting();

	void Update(Vector3 playerPos) override;

private:
	int interval;
	int ShotTimer;

	int shotMax;
	int shotNum;

	int bulletLiveLimit;
	float speed;
};
#pragma once
#include"EnemyState.h"

//射撃
class EnemyShooting : public EnemyState {
public:
	EnemyShooting();

	void Update(Vector3 playerPos) override;

private:
	int interval;
	int ShotTimer;

	int shotMax;
	int shotNum;

	int bulletLiveLimit;
	float speed;
};
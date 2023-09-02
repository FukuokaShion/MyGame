#pragma once
#include"EnemyState.h"

//ŽËŒ‚
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
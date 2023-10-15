/**
 * @file EnemyRoundShooting.h
 * @brief 敵の弾を5つ展開する射撃パターン
 */

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
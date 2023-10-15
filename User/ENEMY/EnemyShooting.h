/**
 * @file EnemyShooting.h
 * @brief 敵の3点バースト射撃パターン
 */

#pragma once
#include"EnemyState.h"

//射撃
class EnemyShooting : public EnemyState {
public:
	EnemyShooting();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;

private:
	int interval;
	int ShotTimer;

	int shotMax;
	int shotNum;

	int bulletLiveLimit;
	float speed;
};
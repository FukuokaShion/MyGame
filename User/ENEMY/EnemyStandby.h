/**
 * @file EnemyStandby.h
 * @brief 敵の待機状態パターン
 *        各行動終了後にこの状態になる
 */

#pragma once
#include"EnemyState.h"

//待機
class Standby : public EnemyState {
public:
	Standby();
	void Update(Vector3 playerPos) override;

private:
	//待機時間
	const int limit = 120;

	//接近移行距離
	const float approachDistance = 4.0f;
};
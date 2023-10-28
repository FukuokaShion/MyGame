/**
 * @file EnemyApproach.h
 * @brief 敵の接近パターン
 */

#pragma once
#include"EnemyState.h"

class Approach : public EnemyState {
public:
	Approach();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;

private:
	//移動速度
	const float speed_ = 0.3f;
	//最終的な距離
	const float distance_ = 4.0f;
	//
	int limit_;
	int timer_;
};
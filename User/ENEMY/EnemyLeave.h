/**
 * @file EnemyLeave.h
 * @brief 敵の離脱パターン
 */

#pragma once
#include"EnemyState.h"

//接近
class Leave : public EnemyState {
public:

	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]]Vector3 playerPos) override;

private:
	//時間
	const int limit_ = 10;
	//移動距離
	const Vector3 distance_ = { 0,0,7 };
};
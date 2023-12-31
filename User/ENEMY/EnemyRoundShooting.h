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

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;

private:
	int interval_;
	int shotTimer_;

	int shotMax_;
	int shotNum_;

	int bulletLiveLimit_;
	float speed_;
};
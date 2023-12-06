/**
 * @file EnemyBombShooting.h
 * @brief 敵の爆弾投下行動
 */

#pragma once
#include"EnemyState.h"
#include"EnemyBomb.h"

 //射撃
class EnemyBombShooting : public EnemyState {
public:
	EnemyBombShooting();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;

private:
	int createTime_;
	int finTime_;
};
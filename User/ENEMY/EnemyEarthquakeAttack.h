/**
 * @file EnemyEarthquakeAttack.h
 * @brief 敵の地震攻撃
 */

#pragma once
#include"EnemyState.h"
#include"EnemyBomb.h"

 //射撃
class EnemyEarthquakeAttack : public EnemyState {
public:
	EnemyEarthquakeAttack();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos) override;

private:
	int attackTime_;
	int finTime_;
};
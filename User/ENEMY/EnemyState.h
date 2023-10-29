/**
 * @file EnemyState.h
 * @brief 敵のステートパターン基底クラス
 */

#pragma once
#include"Transform.h"

class Enemy;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	/**
	 * @brief 敵を本体をセット
	*/
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

public:
	/**
	 * @brief 更新
	*/
	virtual void Update(Vector3 playerPos) = 0;

protected:
	static Enemy* enemy_;
	int timer;
	//プレイヤー座標
	Transform* playerWtf_ = nullptr;

	Vector3 speed_;
	Vector3 velocity_;
};

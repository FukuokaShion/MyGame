/**
 * @file EnemyState.h
 * @brief 敵のステートパターン基底クラス
 */

#pragma once
#include"Transform.h"
#include"GlobalVariables.h"

class Enemy;
using namespace MyEngine;

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
	/**
	 * @brief 調整項目の適用
	*/
	virtual void ApplyGlobalVariables() = 0;

protected:
	static Enemy* enemy_;
	int timer;
	//プレイヤー座標
	Transform* playerWtf_ = nullptr;

	Vector3 speed_;
	Vector3 velocity_;
};

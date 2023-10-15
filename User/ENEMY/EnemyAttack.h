/**
 * EnemyAttack.h
 * 敵の突進攻撃パターン
 */

#pragma once
#include"EnemyState.h"

//攻撃
class Attack : public EnemyState {
public:
	Attack();

	void Update([[maybe_unused]]Vector3 playerPos) override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	///予備動作
	//時間
	const int anticTime = 20;
	//移動距離
	const Vector3 anticDistance = { 0,0,1 };

	///攻撃
	//時間
	const int attackTime = 15;
	//移動距離
	const Vector3 attackDistance = { 0,0,-3 };
	//攻撃力
	const int power = 10;

	///後隙
	const int afterTime = 5;

};
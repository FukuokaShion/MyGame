/**
 * @file EnemyAttack.h
 * @brief 敵の突進攻撃パターン
 */

#pragma once
#include"EnemyState.h"

//攻撃
class Attack : public EnemyState {
public:
	Attack();

	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]]Vector3 playerPos) override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action_;

	///予備動作
	//時間
	const int anticTime_ = 45;
	//移動距離
	const Vector3 anticDistance_ = { 0,0,1 };

	///攻撃
	//時間
	const int attackTime_ = 15;
	//移動距離
	const Vector3 attackDistance_ = { 0,0,-3 };
	//攻撃力
	const int power_ = 220;

	///後隙
	const int afterTime_ = 45;

	//当たり判定
	BaseCollider* attackCol_;
	const float colRad = 3.0f;
};
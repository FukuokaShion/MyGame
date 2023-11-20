/**
 * @file EnemyStrongBodyBlow.h
 * @brief 敵のジャンプ攻撃パターン
 */

#pragma once
#include"EnemyState.h"

 //攻撃
class EnemyStrongBodyBlow : public EnemyState {
public:
	EnemyStrongBodyBlow();

	/**
	 * @brief 更新
	*/
	void Update([[maybe_unused]] Vector3 playerPos) override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
		Dwon,
	};
	Action action_;

	///予備動作
	//時間
	const int anticTime_ = 30;
	

	///攻撃
	//時間
	const int attackTime_ = 35;
	//移動距離
	const Vector3 attackDistance_ = { 0,0,-49 };
	//攻撃力
	const int power_ = 10;

	///プレイヤーに当たった時の後隙
	const int afterTime_ = 30;

	///回避された時の後隙
	const int downTime_ = 60;

	//当たり判定
	BaseCollider* attackCol_;
	const float colRad = 3.0f;
};
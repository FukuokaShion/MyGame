/**
 * @file PlayerAttack.h
 * @brief プレイヤーの攻撃パターン
 */

#pragma once
#include"PlayerState.h"

//攻撃
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();
	/**
	 * @brief 更新
	*/
	void Update() override;

private:
	/**
	 * @brief 状態移行
	*/
	void StateTransition() override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action_;

	Vector3 speed_;
	Vector3 velocity_;

	int timer_;

	///予備動作
	//時間
	const int anticTime_ = 16;
	//移動距離
	const Vector3 anticDistance_ = { 0,0,1 };

	///攻撃
	//時間
	const int attackTime_ = 11;
	//移動距離
	const Vector3 attackDistance_ = { 0,0,1 };
	//攻撃力
	const int sowrdPower_ = 60;

	///後隙
	const int afterTime_ = 6;

	//当たり判定
	BaseCollider* sowrd_;

	//アニメーションスピード
	const float animationSpeed_ = 1.5f;
};
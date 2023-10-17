/**
 * @file PlayerJumpAttack.h
 * @brief プレイヤーのジャンプ攻撃パターン
 */

#pragma once
#include"PlayerState.h"

//攻撃
class PlayerJumpAttack : public PlayerState {
public:
	PlayerJumpAttack();
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
		Attack,
		After,
	};
	Action action;
	int timer;

	//攻撃時
	float attackFallSpeed;
	int power_;

	//後隙
	int afterTime;
};
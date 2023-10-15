/**
 * PlayerJumpAttack.h
 * プレイヤーのジャンプ攻撃パターン
 */

#pragma once
#include"PlayerState.h"

//攻撃
class PlayerJumpAttack : public PlayerState {
public:
	PlayerJumpAttack();
	void Update() override;

private:
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
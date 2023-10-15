/**
 * @file PlayerJump.h
 * @brief プレイヤーのジャンプパターン
 */

#pragma once
#include"PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump();
	void Update() override;

private:
	void StateTransition() override;

private:
	int timer;
	int limit;

	bool up;
};
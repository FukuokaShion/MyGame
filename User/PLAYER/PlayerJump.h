/**
 * @file PlayerJump.h
 * @brief プレイヤーのジャンプパターン
 */

#pragma once
#include"PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump();
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
	int timer;
	int limit;

	bool up;
};
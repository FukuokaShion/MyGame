/**
 * @file PlayerMove.h
 * @brief プレイヤーの移動パターン
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerMove : public PlayerState {
public:
	PlayerMove();
	void Update() override;

private:
	void Move();
	void Rota();

	void StateTransition() override;

private:
	int timer;
	int limit;
};
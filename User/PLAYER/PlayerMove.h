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
	/**
	 * @brief 更新
	*/
	void Update() override;

private:
	/**
	 * @brief 移動
	*/
	void Move();
	/**
	 * @brief 回転
	*/
	void Rota();

	/**
	 * @brief 状態移行
	*/
	void StateTransition() override;

private:
	int timer;
	int limit;
};
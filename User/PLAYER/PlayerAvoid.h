/**
 * @file PlayerAvoid.h
 * @brief プレイヤーの回避パターン
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerAvoid : public PlayerState {
public:
	PlayerAvoid();
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
	const int limit_ = 42;
	int timer_ = limit_;

	Vector3 speed_;
	Vector3 velocity_;

	const float animationSpeed_ = 1.7f;
};
/**
 * @file PlayerStandby.h
 * @brief プレイヤーの待機パターン
 *        各行動後この状態になる
 */

#pragma once
#include"PlayerState.h"

//待機
class PlayerStandby : public PlayerState {
public:
	PlayerStandby();
	void Update() override;

private:
	void StateTransition() override;

};
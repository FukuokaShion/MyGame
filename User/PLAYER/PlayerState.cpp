/**
 * @file PlayerState.cpp
 * @brief プレイヤーのステートパターン基底
 */

#include"PlayerState.h"

Player* PlayerState::player_ = nullptr;

PlayerState::PlayerState() {
	isAttack = false;
	input_ = Input::GetInstance();
	power = 0;
}
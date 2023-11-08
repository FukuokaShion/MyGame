/**
 * @file PlayerState.cpp
 * @brief プレイヤーのステートパターン基底
 */

#include"PlayerState.h"
#include"Player.h"

Player* PlayerState::player_ = nullptr;

PlayerState::PlayerState() {
	isAttack_ = false;
	power_ = Player::Power::ZERO;
}
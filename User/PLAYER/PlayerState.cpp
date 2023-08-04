#include"PlayerState.h"

Player* PlayerState::player_ = nullptr;
Input* PlayerState::input = nullptr;

PlayerState::PlayerState() {
	isAttack = false;
	power = 0;
}
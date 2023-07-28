#include"PlayerState.h"

Player* PlayerState::player_ = nullptr;

PlayerState::PlayerState() {
	isAttack = false;
	power = 0;
}
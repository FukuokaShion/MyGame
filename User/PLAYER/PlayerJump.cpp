/**
 * @file PlayerJump.cpp
 * @brief プレイヤーのジャンプパターン
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerJump.h"
#include"PlayerJumpAttack.h"

#include"Easing.h"

PlayerJump::PlayerJump() {
	player_->AnimationChange(0);
	limit_ = 20;
	timer_ = 0;
	up_ = true;
	player_->PlayWav("jump.wav");
}

void PlayerJump::Update() {
	if (up_ == true) {
		timer_++;
		if (timer_ > limit_) {
			up_ = false;
		}
	}
	else {
		timer_--;
	}

	float t = static_cast<float>(timer_) / static_cast<float>(limit_);

	float newPos = Easing::OutQuad(0, 2, t);

	player_->SetPosY(newPos);

	StateTransition();
}

void PlayerJump::StateTransition() {
	if (player_->GetWtf().position.y <= 0) {
		player_->PlayWav("landing.wav");
		player_->SetPosY(0);
		player_->TransitionTo(new PlayerStandby);
	}
	else {
		if (input_->ButtonInput(B)) {
			player_->TransitionTo(new PlayerJumpAttack);
		}
	}
}
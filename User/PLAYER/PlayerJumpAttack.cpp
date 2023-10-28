/**
 * @file PlayerJumpAttack.cpp
 * @brief プレイヤーのジャンプ攻撃パターン
 */

#include"Player.h"
#include"PlayerJumpAttack.h"
#include"PlayerStandby.h"

PlayerJumpAttack::PlayerJumpAttack() {
	player_->PlayWav("jumpAttack.wav");
	player_->AnimationChange(1, 1.5f);
	attackFallSpeed_ = -0.2f;

	action_ = Action::Attack;
	power_ = 15;

	timer_ = 0;
	afterTime_ = 20;
}

//攻撃
void PlayerJumpAttack::Update() {
	Vector3 velocity;

	switch (action_) {
	case Action::Attack:
		velocity = { 0,attackFallSpeed_,0 };
		player_->Move(velocity);

		//攻撃判定
		isAttack_ = true;
		power_ = power_;

		if (player_->GetWtf().position.y <= 0) {
			player_->SetPosY(0);
			action_ = Action::After;
		}
		break;
	case Action::After:
		timer_++;
		isAttack_ = false;
		if (timer_ > afterTime_) {
			StateTransition();
		}
		break;
	}

}

void PlayerJumpAttack::StateTransition() {
	player_->PlayWav("landing.wav");
	player_->TransitionTo(new PlayerStandby);
}
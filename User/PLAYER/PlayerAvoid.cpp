/**
 * @file PlayerAvoid.cpp
 * @brief プレイヤーの回避パターン
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAvoid.h"

#include"Easing.h"

PlayerAvoid::PlayerAvoid() {
	player_->PlayWav("avoid.wav");
	player_->AnimationChange(Player::Animation::AVOID, animationSpeed_);
	speed_ = { 0,0,0.8f };
	Matrix4 playerMat = player_->GetWtf().matWorld;
	velocity_ = Matrix4::bVelocity(speed_, playerMat);
	timer_ = limit_;
	player_->SetInvincible(true);
}

//待機
void PlayerAvoid::Update() {
	timer_--;

	float t = static_cast<float>(timer_) / static_cast<float>(limit_);

	Vector3 add = Easing::OutQuadVec3({ 0,0,0 }, velocity_, t);

	player_->Move(add);

	if (timer_ < 0) {
		StateTransition();
	}
}

void PlayerAvoid::StateTransition() {
	player_->SetInvincible(false);
	player_->TransitionTo(new PlayerStandby);
}
/**
 * @file PlayerJumpAttack.cpp
 * @brief プレイヤーのジャンプ攻撃パターン
 */

#include"Player.h"
#include"PlayerJumpAttack.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

PlayerJumpAttack::PlayerJumpAttack() {
	player_->PlayWav("jumpAttack.wav");
	animationSpeed = 1.5f;
	player_->AnimationChange(Player::Animation::JUMPATTACK, animationSpeed);
	attackFallSpeed_ = -0.2f;

	action_ = Action::Attack;
	power_ = 100;

	timer_ = 0;
	afterTime_ = 40;

	sowrd_ = new BaseCollider;
	sowrd_->SetAttribute(Attribute::PlayerAttack);
	sowrd_->SetPower(power_);
	CollisionManager::GetInstance()->AddCollider(sowrd_);

	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);
	if (player_->IsRockOn()) {
		player_->RotaY(camAngle);
	}
}

//攻撃
void PlayerJumpAttack::Update() {
	Vector3 velocity;
	const float groundY = 0;

	switch (action_) {
	case Action::Attack:
		velocity = { 0,attackFallSpeed_,0 };
		player_->Move(velocity);

		//攻撃判定
		sowrd_->SetCenter(player_->GetSwordPos());
		isAttack_ = true;
		power_ = power_;

		if (player_->GetWtf().position.y <= groundY) {
			player_->SetPosY(groundY);
			action_ = Action::After;
			CollisionManager::GetInstance()->RemoveCollider(sowrd_);
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
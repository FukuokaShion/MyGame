/**
 * @file PlayerAttack.cpp
 * @brief プレイヤーの攻撃パターン
 */

#include"Player.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

PlayerAttack::PlayerAttack() {
	player_->PlayWav("attack.wav");
	action_ = Action::Antic;
	timer_ = 0;
	player_->AnimationChange(Player::Animation::ATTACK, animationSpeed_);
	
	sowrd_ = new BaseCollider;
	sowrd_->SetAttribute(Attribute::PlayerAttack);
	sowrd_->SetPower(sowrdPower_);
}

//攻撃
void PlayerAttack::Update() {
	timer_++;
	Transform playerWtf = player_->GetWtf();
	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);

	switch (action_) {
	case Action::Antic:
		//予備動作
		speed_ = anticDistance_ / static_cast<float>(anticTime_);
		velocity_ = Matrix4::bVelocity(speed_, playerWtf.matWorld);
		if (player_->IsRockOn()) {
			player_->RotaY(camAngle);
		}
		player_->Move(velocity_);

		if (timer_ > anticTime_) {
			timer_ = 0;
			CollisionManager::GetInstance()->AddCollider(sowrd_);
			action_ = Action::Attack;
		}
		break;
	case Action::Attack:
		//攻撃
		//移動
		speed_ = attackDistance_ / static_cast<float>(attackTime_);
		velocity_ = Matrix4::bVelocity(speed_, playerWtf.matWorld);
		player_->Move(velocity_);

		//パーティクル
		player_->CreateParticle();

		//攻撃判定
		sowrd_->SetCenter(player_->GetSwordPos());
		isAttack_ = true;
		power_ = sowrdPower_;

		if (timer_ > attackTime_) {
			timer_ = 0;
			CollisionManager::GetInstance()->RemoveCollider(sowrd_);
			action_ = Action::After;
		}
		break;
	case Action::After:
		//後隙
		if (timer_ > afterTime_) {
			isAttack_ = false;
			player_->TransitionTo(new PlayerStandby);
		}
		break;
	}
}

void PlayerAttack::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}
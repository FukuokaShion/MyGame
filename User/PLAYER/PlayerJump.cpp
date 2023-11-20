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
	player_->AnimationChange(Player::Animation::JUMP);
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

	float newPos = Easing::OutQuad(groundPos, maxPos, t);

	player_->SetPosY(newPos);

	Rota();
	Move();

	StateTransition();
}

void PlayerJump::Move() {
	//移動量
	Vector3 velocity = { 0,0,0 };
	//移動速度
	float speed = 0.2f;


	//スティック入力角度
	float  sticAngle = atan2f(Input::GetInstance()->GetLeftStickVec().x, Input::GetInstance()->GetLeftStickVec().y);
	//カメラ角度
	float camAngle = atan2f(player_->GetCamViewVec().z, player_->GetCamViewVec().x);
	//カメラから見た時の移動方向に合わせる
	float worldAngle = sticAngle + camAngle;

	velocity = { sinf(worldAngle) * speed,0.0f,cosf(worldAngle) * speed };

	player_->Move(velocity);
}

void PlayerJump::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
		float camAngle = atan2f(player_->GetCamViewVec().z, player_->GetCamViewVec().x);

		player_->RotaY(theta + camAngle);
	}
}

void PlayerJump::StateTransition() {
	if (player_->GetWtf().position.y <= groundPos) {
		player_->PlayWav("landing.wav");
		player_->SetPosY(0);
		player_->TransitionTo(new PlayerStandby);
	}else {
		if (up_ == false) {
			if (Input::GetInstance()->ButtonInput(B)) {
				player_->TransitionTo(new PlayerJumpAttack);
			}
		}
	}
}
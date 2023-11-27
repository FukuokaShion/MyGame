/**
 * @file PlayerMove.cpp
 * @brief プレイヤーの移動パターン
 */

#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"
#include"PlayerJump.h"
#include<cmath>

PlayerMove::PlayerMove() {
	player_->AnimationChange(Player::Animation::DASH);
	limit_ = 600;
	timer_ = 0;

	speed = 0.5f;
	speedTimer_ = 0;
	speedMaxTime_ = 15;
	player_->PlayWav("run.wav");
}

void PlayerMove::Update() {
	Move();
	Rota();
	StateTransition();
}

void PlayerMove::Move() {
	timer_++;
	if (timer_ > limit_) {
		timer_ = 0;
		player_->StopWav();
		player_->PlayWav("run.wav");
	}

	//移動量
	Vector3 velocity = { 0,0,0 };
	//移動速度
	float nowSpeed = nowSpeed = std::lerp(0.0f, speed, speedTimer_ / speedMaxTime_);
	if (speedTimer_ < speedMaxTime_) {
		speedTimer_++;
	}

	//スティック入力角度
	float  sticAngle = atan2f(Input::GetInstance()->GetLeftStickVec().x, Input::GetInstance()->GetLeftStickVec().y);
	//カメラ角度
	float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);
	//カメラから見た時の移動方向に合わせる
	float worldAngle = sticAngle + camAngle;

	velocity = { sinf(worldAngle) * nowSpeed,0.0f,cosf(worldAngle) * nowSpeed };

	player_->Move(velocity);
}

void PlayerMove::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();
		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
		float camAngle = atan2f(player_->GetCamViewVec().x, player_->GetCamViewVec().z);

		player_->RotaY(theta + camAngle);
	}
}

void PlayerMove::StateTransition() {
	//待機状態
	if (Input::GetInstance()->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
		player_->StopWav();
	}
	//ジャンプ
	if (Input::GetInstance()->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerJump);
	}
	//回避
	if (Input::GetInstance()->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAvoid);
	}
	//攻撃
	if (Input::GetInstance()->PButtonTrigger(RB)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
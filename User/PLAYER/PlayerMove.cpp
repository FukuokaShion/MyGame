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

PlayerMove::PlayerMove() {
	player_->AnimationChange(Player::Animation::DASH);
	limit_ = 600;
	timer_ = 0;
	player_->PlayWav("run.wav");
	pushATime_ = 0;
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
	const float speed = 0.5f;

	//スティック入力角度
	float  sticAngle = atan2f(Input::GetInstance()->GetLeftStickVec().x, Input::GetInstance()->GetLeftStickVec().y);
	//カメラ角度
	float camAngle = atan2f(player_->GetCamViewVec().z, player_->GetCamViewVec().x);
	//カメラから見た時の移動方向に合わせる
	float worldAngle = sticAngle + camAngle;

	velocity = { sinf(worldAngle) * speed,0.0f,cosf(worldAngle) * speed };

	player_->Move(velocity);
}

void PlayerMove::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();
		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
		float camAngle = atan2f(player_->GetCamViewVec().z, player_->GetCamViewVec().x);

		player_->RotaY(theta + camAngle);
	}
}

void PlayerMove::StateTransition() {
	//待機状態
	if (Input::GetInstance()->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
		player_->StopWav();
	}

	//
	if (Input::GetInstance()->ButtonInput(A)) {
		pushATime_++;
		if (pushATime_ > switchTime_) {
			//回避
			player_->TransitionTo(new PlayerAvoid);
		}
	}else {
		if (1 <= pushATime_ && pushATime_ <= switchTime_) {
			//ジャンプ
			player_->TransitionTo(new PlayerJump);
		}
		pushATime_ = 0;
	}

	//攻撃
	if (Input::GetInstance()->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
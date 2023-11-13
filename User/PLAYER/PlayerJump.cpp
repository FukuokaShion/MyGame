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

	//スティック入力方向取得
	Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();
	//移動方向に変換
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//単位ベクトル化
	velocity = velocity.nomalize();
	//移動ベクトルに変換
	velocity *= speed;

	//カメラが向いている方向に合わせる
	Transform direction = player_->GetCamWtf();
	direction.rotation.x = 0;
	direction.UpdateMat();
	velocity = Matrix4::bVelocity(velocity, direction.matWorld);
	player_->Move(velocity);
}

void PlayerJump::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		Transform camWtf = player_->GetCamWtf();
		player_->RotaY(theta + camWtf.rotation.y);
	}
}

void PlayerJump::StateTransition() {
	if (player_->GetWtf().position.y <= groundPos) {
		player_->PlayWav("landing.wav");
		player_->SetPosY(0);
		player_->TransitionTo(new PlayerStandby);
	}
	else {
		if (Input::GetInstance()->ButtonInput(B)) {
			player_->TransitionTo(new PlayerJumpAttack);
		}
	}
}
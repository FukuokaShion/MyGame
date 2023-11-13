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
	float speed = 0.5f;

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

void PlayerMove::Rota() {
	if (Input::GetInstance()->LeftStickInput()) {
		Vector2 stickVec = Input::GetInstance()->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		Transform camWtf = player_->GetCamWtf();
		player_->RotaY(theta + camWtf.rotation.y);
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
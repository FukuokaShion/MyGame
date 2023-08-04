#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerMove::PlayerMove() {
	player_->AnimationChange(2);
}

void PlayerMove::Update() {
	Move();
	Rota();
	StateTransition();
}

void PlayerMove::Move() {
	//移動量
	Vector3 velocity = { 0,0,0 };
	//移動速度
	float speed = 0.5f;

	//スティック入力方向取得
	Vector2 stickVec = input->GetLeftStickVec();
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
	if (input->LeftStickInput()) {
		Vector2 stickVec = input->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		Transform camWtf = player_->GetCamWtf();
		player_->RotaY(theta + camWtf.rotation.y);
	}
}

void PlayerMove::StateTransition() {
	if (input->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
	}

	//回避
	if (input->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//攻撃
	if (input->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
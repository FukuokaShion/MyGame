#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerMove::PlayerMove() {
	player_->fbxObject3d_->PlayAnimation(2);
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
	Vector2 stickVec = player_->input_->GetLeftStickVec();
	//移動方向に変換
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//単位ベクトル化
	velocity = velocity.nomalize();
	//移動ベクトルに変換
	velocity *= speed;

	//カメラが向いている方向に合わせる
	Transform direction;
	direction = player_->camera_->wtf;
	direction.rotation.x = 0;
	direction.UpdateMat();
	velocity = Matrix4::bVelocity(velocity, direction.matWorld);
	player_->fbxObject3d_->wtf.position += velocity;

}

void PlayerMove::Rota() {
	if (player_->input_->LeftStickInput()) {
		Vector2 stickVec = player_->input_->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		player_->fbxObject3d_->wtf.rotation.y = theta + player_->camera_->wtf.rotation.y;
	}
}

void PlayerMove::StateTransition() {
	if (player_->input_->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
	}

	//回復
	if (player_->input_->PButtonTrigger(X)) {
		player_->hp->Heal(10);
	}

	//回避
	if (player_->input_->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//攻撃
	if (player_->input_->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
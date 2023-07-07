#include"Action.h"
#include"Approach.h"
#include"Standby.h"

Approach::Approach() {
}

void Approach::Update() {
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerWtf->position, EnemyWtf->position);
	EnemyWtf->rotation.y = angle;

	//速度設定
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//向いている方向に合わせる
	velocity = Matrix4::bVelocity(velocity, EnemyWtf->matWorld);
	
	//座標に足す
	EnemyWtf->position += velocity;

	if (Vector3::Distance(EnemyWtf->position, playerWtf->position) < distance) {
		//一定距離になったら待機状態に移行
		action_->TransitionTo(new Standby);
	}
}
#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyStandby.h"

Approach::Approach() {
	limit = 180;
	timer = limit;
}

void Approach::Update() {
	timer--;
	//プレイヤーの方を向く
	Vector3 angle;
	angle.y = Vector3::Angle(enemy_->playerWtf->position, enemy_->fbxObject3d_->wtf.position);
	enemy_->fbxObject3d_->wtf.rotation = angle;

	//速度設定
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//向いている方向に合わせる
	velocity = Matrix4::bVelocity(velocity, enemy_->fbxObject3d_->wtf.matWorld);

	//座標に足す
	enemy_->fbxObject3d_->wtf.position += velocity;

	if (Vector3::Distance(enemy_->fbxObject3d_->wtf.position, enemy_->playerWtf->position) < distance) {
		//一定距離になったら待機状態に移行
		enemy_->TransitionTo(new Standby);
	}
	if (timer < 0) {
		enemy_->TransitionTo(new Standby);
	}
}
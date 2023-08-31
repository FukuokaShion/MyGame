#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyStandby.h"

Approach::Approach() {
	limit = 180;
	timer = limit;
}

void Approach::Update(Vector3 playerPos) {
	timer--;
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	//速度設定
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//向いている方向に合わせる
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(velocity, enemyMat);

	//座標に足す
	enemy_->Move(velocity);

	if (Vector3::Distance(enemy_->GetWtf().position, playerPos) < distance) {
		//一定距離になったら待機状態に移行
		enemy_->TransitionTo(new Standby);
	}
	if (timer < 0) {
		enemy_->TransitionTo(new Standby);
	}
}
/**
 * @file EnemyApproach.cpp
 * @brief 敵の接近パターン
 */

#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyStandby.h"

Approach::Approach() {
	limit_ = 180;
	timer_ = limit_;
}

void Approach::Update(Vector3 playerPos) {
	timer_--;
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	//速度設定
	velocity_ = { 0,0,0 };
	velocity_ += {0, 0, -speed_};

	//向いている方向に合わせる
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity_ = Matrix4::bVelocity(velocity_, enemyMat);

	//座標に足す
	enemy_->Move(velocity_);

	if (Vector3::Distance(enemy_->GetWtf().position, playerPos) < distance_) {
		//一定距離になったら待機状態に移行
		enemy_->TransitionTo(new Standby);
	}
	if (timer_ < 0) {
		enemy_->TransitionTo(new Standby);
	}
}
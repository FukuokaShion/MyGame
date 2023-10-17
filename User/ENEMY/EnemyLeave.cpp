/**
 * @file EnemyLeave.cpp
 * @brief 敵の離脱パターン
 */

#include"Enemy.h"
#include"EnemyLeave.h"
#include"EnemyStandby.h"

void Leave::Update([[maybe_unused]]Vector3 playerPos) {
	timer++;

	speed = distance / static_cast<float>(limit);
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(speed, enemyMat);

	//座標に足す
	enemy_->Move(velocity);

	if (timer > limit) {
		//待機状態に戻る
		enemy_->TransitionTo(new Standby);
	}
}
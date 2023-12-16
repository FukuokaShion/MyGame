/**
 * @file EnemyBombShooting.cpp
 * @brief 敵の爆弾投下行動
 */

#include"EnemyBombShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyBombShooting::EnemyBombShooting() {
	enemy_->AnimationChange(Enemy::BOMBSHOOT);
	timer = 0;
	createTime_ = 20;
	finTime_ = 140;
}

void EnemyBombShooting::Update(Vector3 playerPos) {
	timer++;
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	if (timer == createTime_) {
		enemy_->CreateBomb();
	}

	if (timer == finTime_) {
		//状態移行
		enemy_->TransitionTo(new Standby);
	}
}
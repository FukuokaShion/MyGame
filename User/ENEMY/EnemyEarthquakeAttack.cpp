/**
 * @file EnemyEarthquakeAttack.cpp
 * @brief 敵の地震攻撃
 */

#include"EnemyEarthquakeAttack.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyEarthquakeAttack::EnemyEarthquakeAttack() {
	enemy_->AnimationChange(Enemy::EARTHQUAKE);
	timer = 0;
	attackTime_ = 70;
	finTime_ = 130;
}

void EnemyEarthquakeAttack::Update(Vector3 playerPos) {
	timer++;
	//プレイヤーの方を向く
	float angle;
	if (timer < attackTime_) {
		angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
		enemy_->RotaY(angle);
	}
	else if (timer == attackTime_) {
		enemy_->CreateEarthquake();
	}else if (timer == finTime_) {
		//状態移行
		enemy_->TransitionTo(new Standby);
	}
}
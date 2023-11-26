/**
 * @file EnemyShooting.cpp
 * @brief 敵の3点バースト射撃パターン
 */

#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->AnimationChange(1);
	interval_ = 25;
	shotTimer_ = interval_;
	shotMax_ = 3;
	shotNum_ = 0;
	bulletLiveLimit_ = 60;
	speed_ = 2;
}

void EnemyShooting::Update(Vector3 playerPos) {
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	shotTimer_--;
	if (shotTimer_ < 0) {
		enemy_->PlayWave("fire.wav");

		//速度設定
		velocity_ = { 0,0,0 };
		velocity_ += {0, 0, -speed_};

		//向いている方向に合わせる
		Matrix4 enemyMat = enemy_->GetWtf().matWorld;
		velocity_ = Matrix4::bVelocity(velocity_, enemyMat);

		//弾生成
		enemy_->CreatBullet(enemy_->GetWtf().position, velocity_, bulletLiveLimit_);

		//次の発射までの時間
		shotTimer_ = interval_;

		//発射数
		shotNum_++;
	}

	//状態移行
	if (shotNum_ >= shotMax_) {
		enemy_->TransitionTo(new Standby);
	}
}
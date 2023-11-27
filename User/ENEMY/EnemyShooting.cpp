/**
 * @file EnemyShooting.cpp
 * @brief 敵の3点バースト射撃パターン
 */

#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->AnimationChange(Enemy::SHOOT);
	interval_ = 25;
	shotTimer_ = interval_;
	shotMax_ = 3;
	shotNum_ = 0;
	bulletLiveLimit_ = 60;
	speed_ = 2;
	afterTime_ = 15;
	timer = 0;
}

void EnemyShooting::Update(Vector3 playerPos) {
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);
	if (shotNum_ < shotMax_) {
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
			Vector3 createPos = enemy_->GetRightHandPos();
			createPos.y -= 1.0f;
			enemy_->CreatBullet(createPos, velocity_, bulletLiveLimit_);

			//次の発射までの時間
			shotTimer_ = interval_;

			//発射数
			shotNum_++;
		}
	}
	//状態移行
	else if (shotNum_ >= shotMax_) {
		timer++;
		if (timer > afterTime_) {
			enemy_->TransitionTo(new Standby);
		}
	}
}
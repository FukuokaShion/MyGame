/**
 * @file EnemyRoundShooting.cpp
 * @brief 敵の弾を5つ展開する射撃パターン
 */

#include"EnemyRoundShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyRoundShooting::EnemyRoundShooting() {
	enemy_->AnimationChange(0);
	interval_ = 25;
	shotTimer_ = interval_;
	shotMax_ = 5;
	shotNum_ = 0;
	bulletLiveLimit_ = 60;
	speed_ = 2;
}

void EnemyRoundShooting::Update(Vector3 playerPos) {
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

		Vector3 creatPos;
		//弾生成
		if (shotNum_ == 0) {
			creatPos = { 1.9f,2.6f,2 };
			creatPos = creatPos * enemyMat;
			enemy_->CreatBullet(creatPos, velocity_, bulletLiveLimit_, interval_ * 4);
		}
		else if (shotNum_ == 1) {
			creatPos = { 1.17f,0.4f,2 };
			creatPos = creatPos * enemyMat;
			enemy_->CreatBullet(creatPos, velocity_, bulletLiveLimit_, interval_ * 3);
		}
		else if (shotNum_ == 2) {
			creatPos = { -1.17f,0.4f,2 };
			creatPos = creatPos * enemyMat;
			enemy_->CreatBullet(creatPos, velocity_, bulletLiveLimit_, interval_ * 2);
		}
		else if (shotNum_ == 3) {
			creatPos = { -1.9f,2.6f,2 };
			creatPos = creatPos * enemyMat;
			enemy_->CreatBullet(creatPos, velocity_, bulletLiveLimit_, interval_ * 1);
		}
		else if (shotNum_ == 4) {
			creatPos = { 0,4,2 };
			creatPos = creatPos * enemyMat;
			enemy_->CreatBullet(creatPos, velocity_, bulletLiveLimit_);
		}


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
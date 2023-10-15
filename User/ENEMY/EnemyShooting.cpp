/**
 * EnemyShooting.cpp
 * 敵の3点バースト射撃パターン
 */

#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->AnimationChange(0);
	interval = 25;
	ShotTimer = interval;
	shotMax = 3;
	shotNum = 0;
	bulletLiveLimit = 60;
	speed = 2;
}

void EnemyShooting::Update(Vector3 playerPos) {
	//プレイヤーの方を向く
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	ShotTimer--;
	if (ShotTimer < 0) {
		enemy_->PlayWave("fire.wav");

		//速度設定
		velocity = { 0,0,0 };
		velocity += {0, 0, -speed};

		//向いている方向に合わせる
		Matrix4 enemyMat = enemy_->GetWtf().matWorld;
		velocity = Matrix4::bVelocity(velocity, enemyMat);

		//弾生成
		enemy_->CreatBullet(enemy_->GetWtf().position, velocity, bulletLiveLimit);

		//次の発射までの時間
		ShotTimer = interval;

		//発射数
		shotNum++;
	}

	//状態移行
	if (shotNum >= shotMax) {
		enemy_->TransitionTo(new Standby);
	}
}
#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->fbxObject3d_->PlayAnimation(0);
	interval = 25;
	ShotTimer = interval;
	shotMax = 3;
	shotNum = 0;
	bulletLiveLimit = 60;
	speed = 2;
}

void EnemyShooting::Update() {
	//プレイヤーの方を向く
	Vector3 angle;
	angle.y = Vector3::Angle(enemy_->playerWtf->position, enemy_->fbxObject3d_->wtf.position);
	enemy_->fbxObject3d_->wtf.rotation = angle;
	
	ShotTimer--;
	if (ShotTimer < 0) {
		
		//速度設定
		Vector3 velocity = { 0,0,0 };
		velocity += {0, 0, -speed};

		//向いている方向に合わせる
		velocity = Matrix4::bVelocity(velocity, enemy_->fbxObject3d_->wtf.matWorld);

		//弾生成
		enemy_->CreatBullet(enemy_->fbxObject3d_->wtf.position, velocity , bulletLiveLimit);
		
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
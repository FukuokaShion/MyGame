#include"Enemy.h"
#include"EnemyLeave.h"
#include"EnemyStandby.h"

void Leave::Update() {
	timer++;

	speed = distance / static_cast<float>(limit);
	velocity = Matrix4::bVelocity(speed, enemy_->fbxObject3d_->wtf.matWorld);

	//座標に足す
	enemy_->fbxObject3d_->wtf.position += velocity;

	if (timer > limit) {
		//待機状態に戻る
		enemy_->TransitionTo(new Standby);
	}
}
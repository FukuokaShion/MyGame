#include"Enemy.h"
#include"EnemyLeave.h"
#include"EnemyStandby.h"

void Leave::Update() {
	timer++;

	speed = distance / static_cast<float>(limit);
	velocity = Matrix4::bVelocity(speed, enemy_->fbxObject3d_->wtf.matWorld);

	//À•W‚É‘«‚·
	enemy_->fbxObject3d_->wtf.position += velocity;

	if (timer > limit) {
		//‘Ò‹@ó‘Ô‚É–ß‚é
		enemy_->TransitionTo(new Standby);
	}
}
#include"Enemy.h"
#include"EnemyAttack.h"
#include"EnemyStandby.h"

Attack::Attack() {
	action = Action::Antic;
}

//UŒ‚
void Attack::Update() {
	timer++;

	switch (action){
	case Action::Antic:
		//—\”õ“®ì
		speed = anticDistance / static_cast<float>(anticTime);
		velocity = Matrix4::bVelocity(speed, enemy_->fbxObject3d_->wtf.matWorld);
		enemy_->fbxObject3d_->wtf.position += velocity;

		if (timer>anticTime) {
			timer = 0;
			action = Action::Attack;
		}
		break;
	case Action::Attack:
		//UŒ‚
		speed = attackDistance / static_cast<float>(attackTime);
		velocity = Matrix4::bVelocity(speed, enemy_->fbxObject3d_->wtf.matWorld);
		enemy_->fbxObject3d_->wtf.position += velocity;

		enemy_->SetIsAttack(true);
		enemy_->setPower(power);
		
		if (timer > attackTime) {
			timer = 0;
			action = Action::After;
		}
		break;
	case Action::After:
		//ŒãŒ„
		if (timer > afterTime) {
			enemy_->SetIsAttack(false);
			enemy_->TransitionTo(new Standby);
		}
		break;
	}
}
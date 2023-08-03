#include"Player.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"

PlayerAttack::PlayerAttack() {
	action = Action::Antic;
	timer = 0;
	player_->fbxObject3d_->PlayAnimation(1,1.5f);
}

//UŒ‚
void PlayerAttack::Update() {
	timer++;
	
	switch (action) {
	case Action::Antic:
		//—\”õ“®ì
		speed = anticDistance / static_cast<float>(anticTime);
		velocity = Matrix4::bVelocity(speed, player_->fbxObject3d_->wtf.matWorld);
		player_->fbxObject3d_->wtf.position += velocity;

		if (timer > anticTime) {
			timer = 0;
			action = Action::Attack;
		}
		break;
	case Action::Attack:
		//UŒ‚
		//ˆÚ“®
		speed = attackDistance / static_cast<float>(attackTime);
		velocity = Matrix4::bVelocity(speed, player_->fbxObject3d_->wtf.matWorld);
		player_->fbxObject3d_->wtf.position += velocity;

		//UŒ‚“–‚½‚è”»’è
		player_->attackHitBox.center = player_->fbxObject3d_->wtf.position;
		player_->attackHitBox.center.y = 2.0;
		player_->attackHitBox.radius = 1.5;

		//UŒ‚”»’è
		isAttack = true;
		power = power_;

		if (timer > attackTime) {
			timer = 0;
			action = Action::After;
		}
		break;
	case Action::After:
		//ŒãŒ„
		if (timer > afterTime) {
			isAttack = false;
			player_->TransitionTo(new PlayerStandby);
		}
		break;
	}
}

void PlayerAttack::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}
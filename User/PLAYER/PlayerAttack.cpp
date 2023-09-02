#include"Player.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"

PlayerAttack::PlayerAttack() {
	player_->PlayWav("attack.wav");
	action = Action::Antic;
	timer = 0;
	player_->AnimationChange(4,1.5f);
}

//UŒ‚
void PlayerAttack::Update() {
	timer++;
	Transform playerWtf = player_->GetWtf();

	switch (action) {
	case Action::Antic:
		//—\”õ“®ì
		speed = anticDistance / static_cast<float>(anticTime);
		velocity = Matrix4::bVelocity(speed, playerWtf.matWorld);
		player_->Move(velocity);

		if (timer > anticTime) {
			timer = 0;
			action = Action::Attack;
		}
		break;
	case Action::Attack:
		//UŒ‚
		//ˆÚ“®
		speed = attackDistance / static_cast<float>(attackTime);
		velocity = Matrix4::bVelocity(speed, playerWtf.matWorld);
		player_->Move(velocity);

		//UŒ‚“–‚½‚è”»’è
		player_->SetAttackPos({ playerWtf.position.x, 2.0f, playerWtf.position.z });
		player_->SetAttackRad(1.5f);

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
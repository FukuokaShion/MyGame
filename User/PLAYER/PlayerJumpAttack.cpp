#include"Player.h"
#include"PlayerJumpAttack.h"
#include"PlayerStandby.h"

PlayerJumpAttack::PlayerJumpAttack() {
	player_->PlayWav("jumpAttack.wav");
	player_->AnimationChange(0, 1.5f);
	attackFallSpeed = -0.2f;

	action = Action::Attack;
	power_ = 15;

	timer = 0;
	afterTime = 20;
}

//�U��
void PlayerJumpAttack::Update() {
	Vector3 velocity;

	switch (action) {
	case Action::Attack:
		velocity = { 0,attackFallSpeed,0 };
		player_->Move(velocity);

		//�U�������蔻��
		player_->SetAttackPos({ player_->GetWtf().position.x, player_->GetWtf().position.y + 2.0f, player_->GetWtf().position.z });
		player_->SetAttackRad(2.0f);

		//�U������
		isAttack = true;
		power = power_;

		if (player_->GetWtf().position.y <= 0) {
			player_->SetPosY(0);
			action = Action::After;
		}
		break;
	case Action::After:
		timer++;
		isAttack = false;
		if (timer > afterTime) {
			StateTransition();
		}
		break;
	}

}

void PlayerJumpAttack::StateTransition() {
	player_->PlayWav("landing.wav");
	player_->TransitionTo(new PlayerStandby);
}
#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerJump.h"
#include"PlayerJumpAttack.h"

#include"Easing.h"

PlayerJump::PlayerJump() {
	player_->AnimationChange(4);
	limit = 20;
	timer = 0;
	up = true;
	player_->PlayWav("jump.wav");
}

void PlayerJump::Update() {
	if (up == true) {
		timer++;
		if (timer > limit) {
			up = false;
		}
	}else {
		timer--;
	}

	float t = static_cast<float>(timer) / static_cast<float>(limit);
	
	float newPos = Easing::OutQuad(0, 2, t);

	player_->SetPosY(newPos);

	StateTransition();
}

void PlayerJump::StateTransition() {
	if (player_->GetWtf().position.y <= 0) {
		player_->PlayWav("landing.wav");
		player_->SetPosY(0);
		player_->TransitionTo(new PlayerStandby);
	}else {
		if (input->ButtonInput(B)) {
			player_->TransitionTo(new PlayerJumpAttack);
		}
	}
}
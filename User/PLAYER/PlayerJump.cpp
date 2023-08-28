#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerJump.h"

#include"Easing.h"

PlayerJump::PlayerJump() {
	player_->AnimationChange(4);
	limit = 20;
	timer = 0;
	up = true;
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

	if (player_->GetWtf().position.y <= 0) {
		player_->SetPosY(0);
		StateTransition();
	}
}

void PlayerJump::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}
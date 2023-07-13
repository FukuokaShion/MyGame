#include"PlayerAction.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"

PlayerAttack::PlayerAttack() {
}

//UŒ‚
void PlayerAttack::Update() {
	timer--;
	if (timer > 15) {
		playerWtf->position += {0, 0.08f , 0};
	}else if(timer > 0) {
		playerWtf->position += {0, -0.13f, 0};
		isAttack = true;
		power = 10;
	}else {
		action_->TransitionTo(new PlayerStandby);
	}
}
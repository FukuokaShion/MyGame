#include"Player.h"

#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerStandby::PlayerStandby() {
	player_->AnimationChange(4);
}

//‘Ò‹@
void PlayerStandby::Update() {
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//‰ñ”ð
	if (input->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//UŒ‚
	if (input->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}

	//ˆÚ“®
	if (input->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}
#include"Player.h"

#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerStandby::PlayerStandby() {
	player_->fbxObject3d_->PlayAnimation(4);
}

//‘Ò‹@
void PlayerStandby::Update() {
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//‰ñ•œ
	if (player_->input_->PButtonTrigger(X)) {
		player_->hp->Heal(10);
	}

	//‰ñ”ð
	if (player_->input_->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//UŒ‚
	if (player_->input_->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}

	//ˆÚ“®
	if (player_->input_->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}
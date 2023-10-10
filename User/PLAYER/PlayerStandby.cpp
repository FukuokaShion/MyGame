#include"Player.h"

#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"
#include"PlayerJump.h"

PlayerStandby::PlayerStandby() {
	player_->AnimationChange(5);
}

//待機
void PlayerStandby::Update() {
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//回避
	//if (input->PButtonTrigger(A)) {
	//	player_->TransitionTo(new PlayerAvoid);
	//}
	if (input_->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerJump);
	}

	//攻撃
	if (input_->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}

	//移動
	if (input_->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}
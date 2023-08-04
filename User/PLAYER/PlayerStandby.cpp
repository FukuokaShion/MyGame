#include"Player.h"

#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerStandby::PlayerStandby() {
	player_->AnimationChange(4);
}

//�ҋ@
void PlayerStandby::Update() {
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//���
	if (input->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//�U��
	if (input->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}

	//�ړ�
	if (input->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}
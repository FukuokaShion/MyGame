#include"PlayerAction.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"

PlayerStandby::PlayerStandby() {
}

//�ҋ@
void PlayerStandby::Update() {
	//��Ԑ؂�ւ�

	if (input_->PushKey(DIK_SPACE)) {
		//���ŃX�y�[�X�L�[�ōU���Ɉڍs
		action_->TransitionTo(new PlayerAttack);
	}
}
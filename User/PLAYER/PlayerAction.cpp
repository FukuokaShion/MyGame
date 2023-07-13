#include"PlayerAction.h"

PlayerAction::PlayerAction(PlayerState* state, Input* input){
	this->TransitionTo(state);
	this->state_->SetInput(input);
}

PlayerAction::~PlayerAction() {
	delete state_;
}

//��Ԃ�ݒ肷��
void PlayerAction::TransitionTo(PlayerState* state) {
	if (this->state_ != nullptr) {
		//�G�ƃv���C���[���W���R�s�[
		Transform* playerWtf = state_->GetPlayerTransform();
		Transform* enemyWtf = state_->GetEnemyTransform();
		Input* input = state_->GetInput();
		//�폜
		delete state_;
		//�V������ԏ�Ԃō쐬
		state_ = state;
		state_->SetAction(this);
		//�G�ƃv���C���[���W���Z�b�g
		state_->SetEnemyTransform(enemyWtf);
		state_->SetPlayerTransform(playerWtf);
		state_->SetInput(input);
	}else {
		//�V�K�쐬
		state_ = state;
		state_->SetAction(this);
	}
}

//���̏�Ԃ̍s��������
void PlayerAction::Update() {
	state_->Update();
}
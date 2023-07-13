#include"EnemyAction.h"

EnemyAction::EnemyAction(EnemyState* state){
	this->TransitionTo(state);
}
EnemyAction::~EnemyAction() {
	delete state_;
}

//��Ԃ�ݒ肷��
void EnemyAction::TransitionTo(EnemyState* state) {
	if (this->state_ != nullptr) {
		//�G�ƃv���C���[���W���R�s�[
		Transform* playerWtf = state_->GetPlayerTransform();
		Transform* enemyWtf = state_->GetEnemyTransform();
		//�폜
		delete state_;
		//�V������ԏ�Ԃō쐬
		state_ = state;
		state_->SetAction(this);
		//�G�ƃv���C���[���W���Z�b�g
		state_->SetEnemyTransform(enemyWtf);
		state_->SetPlayerTransform(playerWtf);
	}else {
		//�V�K�쐬
		state_ = state;
		state_->SetAction(this);
	}
}

//���̏�Ԃ̍s��������
void EnemyAction::Update() {
	state_->Update();
}
#include"Action.h"

Action::Action(EnemyState* state){
	this->TransitionTo(state);
}
Action::~Action() {
	delete state_;
}

//��Ԃ�ݒ肷��
void Action::TransitionTo(EnemyState* state) {
	if (this->state_ != nullptr) {
		delete state_;
	}
	state_ = state;
	state_->SetAction(this);
}

//���̏�Ԃ̍s��������
void Action::Update() {
	state_->Update(wtf);
}
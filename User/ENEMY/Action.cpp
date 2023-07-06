#include"Action.h"

Action::Action(EnemyState* state){
	this->TransitionTo(state);
}
Action::~Action() {
	delete state_;
}

//状態を設定する
void Action::TransitionTo(EnemyState* state) {
	if (this->state_ != nullptr) {
		delete state_;
	}
	state_ = state;
	state_->SetAction(this);
}

//今の状態の行動をする
void Action::Update() {
	state_->Update(wtf);
}
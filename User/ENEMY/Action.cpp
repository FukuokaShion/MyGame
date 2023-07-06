#include"Action.h"

Action::Action(EnemyState* state){
	this->TransitionTo(state);
}
Action::~Action() {
	delete state_;
}

//ó‘Ô‚ðÝ’è‚·‚é
void Action::TransitionTo(EnemyState* state) {
	if (this->state_ != nullptr) {
		delete state_;
	}
	state_ = state;
	state_->SetAction(this);
}

//¡‚Ìó‘Ô‚Ìs“®‚ð‚·‚é
void Action::Update() {
	state_->Update(wtf);
}
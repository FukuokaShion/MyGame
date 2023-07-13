#include"PlayerAction.h"

PlayerAction::PlayerAction(PlayerState* state, Input* input){
	this->TransitionTo(state);
	this->state_->SetInput(input);
}

PlayerAction::~PlayerAction() {
	delete state_;
}

//状態を設定する
void PlayerAction::TransitionTo(PlayerState* state) {
	if (this->state_ != nullptr) {
		//敵とプレイヤー座標をコピー
		Transform* playerWtf = state_->GetPlayerTransform();
		Transform* enemyWtf = state_->GetEnemyTransform();
		Input* input = state_->GetInput();
		//削除
		delete state_;
		//新しい状態状態で作成
		state_ = state;
		state_->SetAction(this);
		//敵とプレイヤー座標をセット
		state_->SetEnemyTransform(enemyWtf);
		state_->SetPlayerTransform(playerWtf);
		state_->SetInput(input);
	}else {
		//新規作成
		state_ = state;
		state_->SetAction(this);
	}
}

//今の状態の行動をする
void PlayerAction::Update() {
	state_->Update();
}
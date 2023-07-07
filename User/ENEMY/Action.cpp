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
		//敵とプレイヤー座標をコピー
		Transform* playerWtf = state_->GetPlayerTransform();
		Transform* enemyWtf = state_->GetEnemyTransform();
		//削除
		delete state_;
		//新しい状態状態で作成
		state_ = state;
		state_->SetAction(this);
		//敵とプレイヤー座標をセット
		state_->SetEnemyTransform(enemyWtf);
		state_->SetPlayerTransform(playerWtf);
	}else {
		//新規作成
		state_ = state;
		state_->SetAction(this);
	}
}

//今の状態の行動をする
void Action::Update() {
	state_->Update();
}
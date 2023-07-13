#pragma once
#include"PlayerState.h"


class PlayerAction {
public:
	PlayerAction(PlayerState* state, Input* input);
	~PlayerAction();

	void TransitionTo(PlayerState* state);
	void SetEnemyTransform(Transform* EnemyWtf) { state_->SetEnemyTransform(EnemyWtf); };
	void SetTransform(Transform* playerWtf) { state_->SetPlayerTransform(playerWtf); };

	bool GetIsAttack() { return state_->GetIsAttack(); };
	int GetPower() { return state_->GetPower(); };

	void Update();

private:
	PlayerState* state_ = nullptr;

	//待機
	//攻撃
	//ダッシュ
};
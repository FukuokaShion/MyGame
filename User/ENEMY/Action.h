#pragma once
#include"EnemyState.h"


class Action {
public:
	Action(EnemyState* state);
	~Action();

	void TransitionTo(EnemyState* state);
	void SetTransform(Transform* EnemyWtf) { state_->SetEnemyTransform(EnemyWtf); };
	void SetPlayerTransform(Transform* playerWtf) { state_->SetPlayerTransform(playerWtf); };

	void Update();

private:
	EnemyState* state_ = nullptr;
};
#pragma once
#include"EnemyState.h"


class Action {
public:
	Action(EnemyState* state);
	~Action();

	void TransitionTo(EnemyState* state);

	void SetTransform(Transform* wtf) { this->wtf = wtf; };

	void Update();

private:
	EnemyState* state_ = nullptr;
	Transform* wtf = nullptr;
};
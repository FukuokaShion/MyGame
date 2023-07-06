#pragma once
#include"Transform.h"

class Action;

class EnemyState {
protected:
	Action* action_;

public:
	virtual ~EnemyState() {};

	void SetAction(Action* action) { this->action_ = action; }

public:
	virtual void Update(Transform* wtf) = 0;
};

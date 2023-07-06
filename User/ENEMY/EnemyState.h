#pragma once
#include"Transform.h"

class Action;

class EnemyState {
public:
	virtual ~EnemyState() {};

	void SetAction(Action* action) { this->action_ = action; }
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };
	void SetEnemyTransform(Transform* EnemyWtf) { this->EnemyWtf = EnemyWtf; };

	Transform* GetPlayerTransform() { return playerWtf; };
	Transform* GetEnemyTransform() { return EnemyWtf; };

public:
	virtual void Update() = 0;

protected:
	Action* action_;

	Transform* playerWtf;
	Transform* EnemyWtf;
};

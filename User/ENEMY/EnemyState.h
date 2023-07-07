#pragma once
#include"Transform.h"

class Action;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	void SetAction(Action* action) { this->action_ = action; }
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };
	void SetEnemyTransform(Transform* EnemyWtf) { this->EnemyWtf = EnemyWtf; };

	Transform* GetPlayerTransform() { return playerWtf; };
	Transform* GetEnemyTransform() { return EnemyWtf; };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };

public:
	virtual void Update() = 0;

protected:
	Action* action_ = nullptr;

	//ç¿ïW
	Transform* playerWtf = nullptr;
	Transform* EnemyWtf = nullptr;

	//çUåÇîªíË
	bool isAttack;
	int power;
};

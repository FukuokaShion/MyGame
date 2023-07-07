#pragma once
#include"Transform.h"

class EnemyAction;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	void SetAction(EnemyAction* action) { this->action_ = action; }
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };
	void SetEnemyTransform(Transform* EnemyWtf) { this->EnemyWtf = EnemyWtf; };

	Transform* GetPlayerTransform() { return playerWtf; };
	Transform* GetEnemyTransform() { return EnemyWtf; };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };

public:
	virtual void Update() = 0;

protected:
	EnemyAction* action_ = nullptr;

	//���W
	Transform* playerWtf = nullptr;
	Transform* EnemyWtf = nullptr;

	//�U������
	bool isAttack;
	int power;
};

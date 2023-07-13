#pragma once
#include"Transform.h"
#include"Input.h"

class PlayerAction;

class PlayerState {
public:
	PlayerState();
	virtual ~PlayerState() {};

	void SetAction(PlayerAction* action) { this->action_ = action; }
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };
	void SetEnemyTransform(Transform* EnemyWtf) { this->enemyWtf = EnemyWtf; };
	void SetInput(Input* input) { this->input_ = input; };

	Transform* GetPlayerTransform() { return playerWtf; };
	Transform* GetEnemyTransform() { return enemyWtf; };
	Input* GetInput() { return input_; };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };

public:
	virtual void Update() = 0;

protected:
	PlayerAction* action_ = nullptr;

	//“ü—Í
	Input* input_ = nullptr;

	//À•W
	Transform* playerWtf = nullptr;
	Transform* enemyWtf = nullptr;

	//UŒ‚”»’è
	bool isAttack;
	int power;
};

#pragma once
#include"Transform.h"
#include"Input.h"

class Player;

class PlayerState {
public:
	PlayerState();
	virtual ~PlayerState() {};

	void SetPlayer(Player* player) { player_ = player; };
	void SetInput(Input* input) { this->input = input; };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };

	//XV
	virtual void Update() = 0;

protected:
	//ó‘ÔˆÚs
	virtual void StateTransition() = 0;

protected:
	static Player* player_;
	static Input* input;

	//UŒ‚”»’è
	bool isAttack;
	int power;
};

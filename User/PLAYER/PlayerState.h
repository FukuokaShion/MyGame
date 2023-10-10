#pragma once
#include"Transform.h"
#include"Input.h"

class Player;

class PlayerState {
public:
	PlayerState();
	virtual ~PlayerState() {};

	void SetPlayer(Player* player) { player_ = player; };
	void SetInput(Input* input) { this->input_ = input; };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };

	//更新
	virtual void Update() = 0;

protected:
	//状態移行
	virtual void StateTransition() = 0;

protected:
	static Player* player_;
	static Input* input_;

	//攻撃判定
	bool isAttack;
	int power;
};

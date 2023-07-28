#pragma once
#include"PlayerState.h"

//UŒ‚
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();
	void Update() override;

private:
	void StateTransition() override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	Vector3 speed;
	Vector3 velocity;

	int timer;

	///—\”õ“®ì
	//ŠÔ
	const int anticTime = 16;
	//ˆÚ“®‹——£
	const Vector3 anticDistance = { 0,0,2 };

	///UŒ‚
	//ŠÔ
	const int attackTime = 11;
	//ˆÚ“®‹——£
	const Vector3 attackDistance = { 0,0,1 };
	//UŒ‚—Í
	const int power_ = 10;

	///ŒãŒ„
	const int afterTime = 6;
};
#pragma once
#include"PlayerState.h"

//UŒ‚
class PlayerJumpAttack : public PlayerState {
public:
	PlayerJumpAttack();
	void Update() override;

private:
	void StateTransition() override;

private:
	enum class Action {
		Attack,
		After,
	};
	Action action;
	int timer;
	
	//UŒ‚
	float attackFallSpeed;
	int power_;

	//ŒãŒ„
	int afterTime;
};
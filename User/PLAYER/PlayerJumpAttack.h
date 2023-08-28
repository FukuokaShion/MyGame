#pragma once
#include"PlayerState.h"

//�U��
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
	
	//�U����
	float attackFallSpeed;
	int power_;

	//�㌄
	int afterTime;
};
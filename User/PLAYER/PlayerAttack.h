#pragma once
#include"PlayerState.h"

//�U��
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();

	void Update() override;

private:
	const int limit = 40;
	int timer = limit;

};
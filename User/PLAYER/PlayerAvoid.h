#pragma once
#include"PlayerState.h"

//‘Ò‹@
class PlayerAvoid : public PlayerState {
public:
	PlayerAvoid();
	void Update() override;

private:
	void StateTransition() override;

private:
	const int limit = 42;
	int timer = limit;

	Vector3 speed;
	Vector3 velocity;
};
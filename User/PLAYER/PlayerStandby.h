#pragma once
#include"PlayerState.h"

//待機
class PlayerStandby : public PlayerState {
public:
	PlayerStandby();
	void Update() override;

private:
	void StateTransition() override;

};
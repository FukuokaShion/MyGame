#pragma once
#include"PlayerState.h"

//�ҋ@
class PlayerStandby : public PlayerState {
public:
	PlayerStandby();

	void Update() override;
};
#pragma once
#include"PlayerState.h"

//‘Ò‹@
class PlayerStandby : public PlayerState {
public:
	PlayerStandby();

	void Update() override;
};
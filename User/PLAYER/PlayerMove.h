#pragma once
#include"PlayerState.h"

//‘Ò‹@
class PlayerMove : public PlayerState {
public:
	PlayerMove();
	void Update() override;

private:
	void Move();
	void Rota();

	void StateTransition() override;

};
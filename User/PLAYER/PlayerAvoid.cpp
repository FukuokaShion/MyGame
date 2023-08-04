#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAvoid.h"

PlayerAvoid::PlayerAvoid() {
	player_->AnimationChange(3, 1.7f);
	speed = { 0,0,0.8f };
	Matrix4 playerMat = player_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(speed, playerMat);
	timer = limit;
}

//‘Ò‹@
void PlayerAvoid::Update() {
	timer--;

	player_->Move(velocity);

	if (timer < 0) {
	StateTransition();
	}
}

void PlayerAvoid::StateTransition() {
	player_->TransitionTo(new PlayerStandby);

}
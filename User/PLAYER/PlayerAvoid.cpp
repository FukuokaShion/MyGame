#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAvoid.h"

#include"Easing.h"

PlayerAvoid::PlayerAvoid() {
	player_->PlayWav("avoid.wav");
	player_->AnimationChange(3, 1.7f);
	speed = { 0,0,0.8f };
	Matrix4 playerMat = player_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(speed, playerMat);
	timer = limit;
}

//待機
void PlayerAvoid::Update() {
	timer--;

	float t = static_cast<float>(timer) / static_cast<float>(limit);

	Vector3 add = Easing::OutQuadVec3({ 0,0,0 }, velocity, t);

	player_->Move(add);

	if (timer < 0) {
		StateTransition();
	}
}

void PlayerAvoid::StateTransition() {
	player_->TransitionTo(new PlayerStandby);

}
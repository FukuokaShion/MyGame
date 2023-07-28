#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAvoid.h"

PlayerAvoid::PlayerAvoid() {
	player_->fbxObject3d_->PlayAnimation(3, 1.7f);
	speed = { 0,0,0.8f };
	velocity = Matrix4::bVelocity(speed, player_->fbxObject3d_->wtf.matWorld);
	timer = limit;
}

//‘Ò‹@
void PlayerAvoid::Update() {
	timer--;

	player_->fbxObject3d_->wtf.position += velocity;

	if (timer < 0) {
	StateTransition();
	}
}

void PlayerAvoid::StateTransition() {
	player_->TransitionTo(new PlayerStandby);

}
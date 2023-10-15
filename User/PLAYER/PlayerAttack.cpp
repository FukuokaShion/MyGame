/**
 * PlayerAttack.cpp
 * プレイヤーの攻撃パターン
 */

#include"Player.h"
#include"PlayerAttack.h"
#include"PlayerStandby.h"
#include"CollisionManager.h"

PlayerAttack::PlayerAttack() {
	player_->PlayWav("attack.wav");
	action = Action::Antic;
	timer = 0;
	player_->AnimationChange(4, 1.5f);
	
	sowrd = new BaseCollider;
	sowrd->SetAttribute(Attribute::PlayerAttack);
}

//攻撃
void PlayerAttack::Update() {
	timer++;
	Transform playerWtf = player_->GetWtf();

	switch (action) {
	case Action::Antic:
		//予備動作
		speed = anticDistance / static_cast<float>(anticTime);
		velocity = Matrix4::bVelocity(speed, playerWtf.matWorld);
		player_->Move(velocity);

		if (timer > anticTime) {
			timer = 0;
			CollisionManager::GetInstance()->AddCollider(sowrd);
			action = Action::Attack;
		}
		break;
	case Action::Attack:
		//攻撃
		//移動
		speed = attackDistance / static_cast<float>(attackTime);
		velocity = Matrix4::bVelocity(speed, playerWtf.matWorld);
		player_->Move(velocity);

		//攻撃判定
		sowrd->SetCenter({ 0,0,0 });
		isAttack = true;
		power = power_;

		if (timer > attackTime) {
			timer = 0;
			CollisionManager::GetInstance()->RemoveCollider(sowrd);
			action = Action::After;
		}
		break;
	case Action::After:
		//後隙
		if (timer > afterTime) {
			isAttack = false;
			player_->TransitionTo(new PlayerStandby);
		}
		break;
	}
}

void PlayerAttack::StateTransition() {
	player_->TransitionTo(new PlayerStandby);
}
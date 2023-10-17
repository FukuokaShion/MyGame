/**
 * @file EnemyAttack.cpp
 * @brief 敵の突進攻撃パターン
 */

#include"Enemy.h"
#include"EnemyAttack.h"
#include"EnemyStandby.h"

Attack::Attack() {
	action = Action::Antic;
	enemy_->AnimationChange(0);
}

//攻撃
void Attack::Update([[maybe_unused]] Vector3 playerPos) {
	timer++;

	Matrix4 enemyMat = enemy_->GetWtf().matWorld;

	switch (action) {
	case Action::Antic:
		//予備動作
		speed = anticDistance / static_cast<float>(anticTime);
		velocity = Matrix4::bVelocity(speed, enemyMat);
		enemy_->Move(velocity);

		if (timer > anticTime) {
			timer = 0;
			action = Action::Attack;
		}
		break;
	case Action::Attack:
		//攻撃
		enemy_->PlayWave("enemyat.wav");
		speed = attackDistance / static_cast<float>(attackTime);
		velocity = Matrix4::bVelocity(speed, enemyMat);
		enemy_->Move(velocity);

		enemy_->SetIsAttack(true);
		enemy_->setPower(power);

		if (timer > attackTime) {
			timer = 0;
			action = Action::After;
		}
		break;
	case Action::After:
		//後隙
		if (timer > afterTime) {
			enemy_->SetIsAttack(false);
			enemy_->TransitionTo(new Standby);
		}
		break;
	}
}
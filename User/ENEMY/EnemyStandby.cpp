#include"Enemy.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"
#include"EnemyLeave.h"
#include"EnemyShooting.h"
#include"EnemyRoundShooting.h"

Standby::Standby() {
	enemy_->AnimationChange(1);
}

//待機
void Standby::Update(Vector3 playerPos) {
	timer++;
	//状態切り替え
	if (timer > limit) {
		if (Vector3::Distance(enemy_->GetWtf().position, playerPos) > approachDistance) {
			if (rand() % 100 + 1 < 50) {
				enemy_->TransitionTo(new Approach);
			}
			else {
				enemy_->TransitionTo(new EnemyShooting);
			}
		}
		else {
			if (rand() % 100 + 1 < 50) {
				enemy_->TransitionTo(new Attack);
			}
			else {
				enemy_->TransitionTo(new Leave);
			}
		}
	}
}
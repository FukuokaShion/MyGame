/**
 * @file EnemyStandby.cpp
 * @brief 敵の待機状態パターン
 *        各行動終了後にこの状態になる
 */

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
	if (timer > limit_) {
		if (Vector3::Distance(enemy_->GetWtf().position, playerPos) > approachDistance_) {
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
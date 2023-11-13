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
	enemy_->AnimationChange(Enemy::Animation::STAND);
}

//待機
void Standby::Update(Vector3 playerPos) {
	timer++;
	//状態切り替え
	if (timer > limit_) {
		int randNum = rand() % 100 + 1;//1から100の範囲になる
		//遠い場合
		if (Vector3::Distance(enemy_->GetWtf().position, playerPos) > approachDistance_) {
			if (0 < randNum && randNum <= 30) {
				enemy_->TransitionTo(new Approach);
			}else if (30 < randNum && randNum <= 100) {
				enemy_->TransitionTo(new EnemyShooting);
			}
			/*else {
				enemy_->TransitionTo(new EnemyRoundShooting);
			}*/
		}
		//近い場合
		else {
			if (0 < randNum && randNum <= 70) {
				enemy_->TransitionTo(new Attack);
			}else {
				enemy_->TransitionTo(new Leave);
			}
		}
	}
}
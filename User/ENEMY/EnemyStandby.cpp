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
#include"EnemyStrongBodyBlow.h"
#include"EnemyBombShooting.h"
#include"EnemyEarthquakeAttack.h"

Standby::Standby() {
	enemy_->AnimationChange(Enemy::STAND);
}

//待機
void Standby::Update(Vector3 playerPos) {
	timer++;
	playerPos;
	//状態切り替え
	if (timer > limit_) {
		int randNum = rand() % 100 + 1;//1から100の範囲になる
		//遠い場合
		if (Vector3::Distance(enemy_->GetWtf().position, playerPos) > approachDistance_) {
			if (0 < randNum && randNum <= 20) {
				enemy_->TransitionTo(new Approach);
			}else if (20 < randNum && randNum <= 60) {
				enemy_->TransitionTo(new EnemyShooting);
			}else if(60 < randNum && randNum <= 75) {
				enemy_->TransitionTo(new EnemyRoundShooting);
			}else {
				enemy_->TransitionTo(new EnemyBombShooting);
			}
		}
		//近い場合
		else {
			if (0 < randNum && randNum <= 35) {
				enemy_->TransitionTo(new Attack);
			}else if (35 < randNum && randNum <= 55) {
				enemy_->TransitionTo(new EnemyShooting);
			}else if (55 < randNum && randNum <= 85) {
				enemy_->TransitionTo(new EnemyEarthquakeAttack);
			}else {
				enemy_->TransitionTo(new Leave);
			}
		}
	}
}
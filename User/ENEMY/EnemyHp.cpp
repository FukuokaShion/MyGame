/**
 * @file EnemyHp.cpp
 * @brief 敵の体力を管理する
 */

#include"EnemyHp.h"

EnemyHp::EnemyHp() {
	MaxHp_ = 1000;
	hp_ = MaxHp_;
	isLive_ = true;
}

EnemyHp::~EnemyHp() {
}

void EnemyHp::Initialize() {
	hp_ = MaxHp_;
	isLive_ = true;
}

void EnemyHp::Damage(int damage) {
	hp_ -= damage;
	if (hp_ <= 0) {
		isLive_ = false;
	}
}

void EnemyHp::Heal(int heal) {
	hp_ += heal;
	if (hp_ > MaxHp_) {
		hp_ = MaxHp_;
	}
}
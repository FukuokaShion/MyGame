/**
 * @file EnemyHp.cpp
 * @brief 敵の体力を管理する
 */

#include"EnemyHp.h"

EnemyHp::EnemyHp() {
	MaxHp = 100;
	hp = MaxHp;
	isLive = true;
}

EnemyHp::~EnemyHp() {
}

void EnemyHp::Initialize() {
	hp = MaxHp;
	isLive = true;
}

void EnemyHp::Damage(int damage) {
	hp -= damage;
	if (hp <= 0) {
		isLive = false;
	}
}

void EnemyHp::Heal(int heal) {
	hp += heal;
	if (hp > MaxHp) {
		hp = MaxHp;
	}
}
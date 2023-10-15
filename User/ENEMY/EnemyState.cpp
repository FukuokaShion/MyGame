/**
 * @file EnemyState.cpp
 * @brief 敵のステートパターン基底クラス
 */

#include"EnemyState.h"

Enemy* EnemyState::enemy_ = nullptr;

EnemyState::EnemyState() {
	timer = 0;
	speed = { 0,0,0 };
	velocity = { 0,0,0 };
}
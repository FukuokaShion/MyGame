#pragma once
#include"Transform.h"

class Enemy;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	void SetEnemy(Enemy* enemy) { this->enemy_ = enemy; }

public:
	virtual void Update() = 0;

protected:
	Enemy* enemy_ = nullptr;
	int timer;
	Vector3 speed;
	Vector3 velocity;
};

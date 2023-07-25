#pragma once
#include"Transform.h"

class Enemy;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

public:
	virtual void Update() = 0;

protected:
	static Enemy* enemy_;
	int timer;
	Vector3 speed;
	Vector3 velocity;
};

#pragma once
#include"Transform.h"

class Enemy;

class EnemyState {
public:
	EnemyState();
	virtual ~EnemyState() {};

	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

public:
	virtual void Update(Vector3 playerPos) = 0;

protected:
	static Enemy* enemy_;
	int timer;
	//プレイヤー座標
	Transform* playerWtf = nullptr;
	
	Vector3 speed;
	Vector3 velocity;
};

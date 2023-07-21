#pragma once
#include"CollisionPrimitive.h"

class Enemy;
class Player;

class CollisionManager {
public:
	static void CheckCollision();
	static Vector3 Body2Body();

	static void SetPlayer(Player* player) { player_ = player; };
	static void SetEnemy(Enemy* enemy) { enemy_ = enemy; };

private:
	static Player* player_;
	static Enemy* enemy_;

	static bool isPlayerHit;
	static bool isEnemyHit;
};
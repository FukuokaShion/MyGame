#pragma once
#include"Player.h"
#include"Enemy.h"

class CollisionManager {
public:
	void CheckCollision();

	void SetPlayer(Player* player) { this->player = player; };
	void SetEnemy(Enemy* enemy) { this->enemy = enemy; };

private:
	Player* player = nullptr;
	Enemy* enemy = nullptr;

	bool isPlayerHit;
	bool isEnemyHit;
};
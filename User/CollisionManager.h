#pragma once
#include"CollisionPrimitive.h"
#include<forward_list>

class Enemy;
class Player;

class CollisionManager {

public:
	static CollisionManager* GetInstance();

	static void SetPlayer(Player* player) { player_ = player; };
	static void SetEnemy(Enemy* enemy) { enemy_ = enemy; };

	void AddCollider(Sphere* collide) { colliders.push_front(collide); };
	void RemoveCollider(Sphere* collide) { colliders.remove(collide); };

	void CheakCol();

	static void CheckCollision();
	static Vector3 Body2Body();
private:
	static Player* player_;
	static Enemy* enemy_;

	static bool isPlayerHit;
	static bool isEnemyHit;
	std::forward_list<Sphere*> colliders;
};
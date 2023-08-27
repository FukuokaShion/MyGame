#pragma once
#include"CollisionPrimitive.h"
#include<forward_list>

class Enemy;
class Player;

class CollisionManager {
public:
	static void CheckCollision();
	static Vector3 Body2Body();

	static void SetPlayer(Player* player) { player_ = player; };
	static void SetEnemy(Enemy* enemy) { enemy_ = enemy; };


	inline void AddCollider(Sphere* collide) { colliders.push_front(collide); };
	inline void RemoveCollider(Sphere* collide) { colliders.remove(collide); };
	

	static CollisionManager* GetInstance();
	void CheakCol();
private:
	static Player* player_;
	static Enemy* enemy_;

	static bool isPlayerHit;
	static bool isEnemyHit;


	std::forward_list<Sphere*> colliders;
};
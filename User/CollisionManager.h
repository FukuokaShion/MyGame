#pragma once
#include"CollisionPrimitive.h"
#include<forward_list>

class CollisionManager {
public:
	static CollisionManager* GetInstance();

	void AddCollider(BaseCollider* collide) { colliders.push_front(collide); };
	void RemoveCollider(BaseCollider* collide) { colliders.remove(collide); };

	void CheakCol();
private:
	bool isPlayerHit;
	bool isEnemyHit;
	std::forward_list<BaseCollider*> colliders;
};
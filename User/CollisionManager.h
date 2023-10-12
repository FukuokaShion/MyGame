#pragma once
#include"CollisionPrimitive.h"
#include<forward_list>
#include"Model.h"
#include"Object3d.h"

class CollisionManager {
public:
	~CollisionManager();

	void Initialize();

	static CollisionManager* GetInstance();

	void AddCollider(BaseCollider* collide);
	void RemoveCollider(BaseCollider* collide);

	void CheakCol();
private:
	bool isPlayerHit;
	bool isEnemyHit;
	std::forward_list<BaseCollider*> colliders;

public://可視化関数
	void DrawCollider();

private://可視化変数
	Model* model_ = nullptr;
	int maxCol = 20;
	Object3d* objects_[20];
};
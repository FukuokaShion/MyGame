#pragma once
#include "Object3d.h"
#include "Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

	static void StaticInitialize();
	static void StaticFinalize();
	void Initialize(Vector3 pos, Vector3 velocity, int liveLimit,int stayTime = 0);

	void Update();

	void Draw();

	bool IsDead() { return isDead; };

private:
	Object3d* obj = nullptr;
	static Model* model;

	int liveTimer;
	Vector3 velocity;
	int stayTime;
	bool isDead;

	Sphere* sphere;
};
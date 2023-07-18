#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"

#include"EnemyAction.h"
#include"EnemyHp.h"

class Player;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();
	void SetPlayerTransform(Transform* playerWtf);

	void Update();
	void Draw();

	bool GetIsAttack() { return action->GetIsAttack(); };
	int GetPower() { return action->GetPower(); };

	void OnCollision(int damage);


public:
	//体当たり判定
	Cylinder bodyHitBox;

	//攻撃当たり判定
	Sphere attackHitBox;
private:
	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//行動
	EnemyAction* action = nullptr;
	//ステータス
	EnemyHp* hp = nullptr;
};
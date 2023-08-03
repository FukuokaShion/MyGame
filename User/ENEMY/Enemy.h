#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"

#include"EnemyHp.h"
#include"EnemyState.h"

class Player;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };

	void Update();
	void Draw();

	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; };
	void setPower(int power) { this->power = power; };

	void OnCollision(int damage,Vector3 hitPos);

	void TransitionTo(EnemyState* state);

	bool IsLive() { return hp->IsLive(); };

public:
	//体当たり判定
	Cylinder bodyHitBox;
	//攻撃当たり判定
	Sphere attackHitBox;
	//プレイヤー座標
	Transform* playerWtf = nullptr;
	//オブジェクト
	FBXObject3d* fbxObject3d_ = nullptr;

private:
	//モデル
	FBXModel* fbxModel_ = nullptr;

	//行動
	EnemyState* state_ = nullptr;
	//ステータス
	EnemyHp* hp = nullptr;

	//攻撃判定
	bool isAttack;
	int power;

	EnemyParticle* particle = nullptr;
};
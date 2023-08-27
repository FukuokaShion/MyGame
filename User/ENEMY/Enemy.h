#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"

#include"EnemyHp.h"
#include"EnemyState.h"
#include"EnemyBullet.h"

class Player;

class Enemy {
public:
	//設定
	Enemy();
	~Enemy();
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();
	void ObjDraw();

	//状態以降
	void TransitionTo(EnemyState* state);

	//座標
	
	//プレイヤー座標
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };

	//攻撃当たり判定
	Sphere GetAttackHitBox() { return attackHitBox; };
	void SetAttackRad(float newRad) { attackHitBox.radius = newRad; };
	void SetAttackPos(Vector3 newPos) { attackHitBox.center = newPos; };

	//体当たり判定
	Cylinder GetBodyHitBox() { return bodyHitBox; };

	//被ダメ処理
	void OnCollision(int damage, Vector3 hitPos);

	//ステータス
	bool IsLive() { return hp->IsLive(); };
	int GetHp() { return hp->GetHp(); };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; };
	void setPower(int power) { this->power = power; };

	//弾生成
	void CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

public:
	//プレイヤー座標
	Transform* playerWtf = nullptr;
	
	//オブジェクト
	FBXObject3d* fbxObject3d_ = nullptr;

	//球
	std::list<std::unique_ptr<EnemyBullet>> bullets;
private:
	//行動
	EnemyState* state_ = nullptr;
	
	//体力
	EnemyHp* hp = nullptr;

	//体当たり判定
	Cylinder bodyHitBox;

	//攻撃当たり判定
	Sphere attackHitBox;

	//モデル
	FBXModel* fbxModel_ = nullptr;

	//攻撃判定
	bool isAttack;
	int power;

	EnemyParticle* particle = nullptr;

	//弾

};
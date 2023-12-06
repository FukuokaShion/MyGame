/**
 * @file EnemyBomb.h
 * @brief 敵の爆弾
 */

#pragma once
#include "Object3d.h"
#include "Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

class EnemyBomb{
public:
	EnemyBomb();
	~EnemyBomb();

	/**
	 * @brief 静的初期化
	*/
	static void StaticInitialize();

	/**
	 * @brief 静的破棄
	*/
	static void StaticFinalize();

	/**
	 * @brief 初期化
	*/
	void Initialize(Vector3 creatPos);

	/**
	 * @brief 更新
	*/
	void Update(Vector3 stayPos, Vector3 playerPos);

	/**
	 * @brief 描画
	*/
	void Draw();

	/**
	 * @brief 更新
	*/
	bool IsDead() { return isDead_; };

private:
	//モデル
	Object3d* obj_ = nullptr;
	static Model* model_;
	BaseCollider* sphere_;

	//待機
	int stayTime_;
	float startRad_;

	//移動
	Vector3 velocity_;
	float speed_;

	//爆発
	int explosionTime_;
	bool isExplosion_;
	float maxRad_;
	float sizeChangeRate_;

	//全体
	int timer_;
	bool isFired_;
	int liveTimer_;
	bool isDead_;
};
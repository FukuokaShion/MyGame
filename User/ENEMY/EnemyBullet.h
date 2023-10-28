/**
 * @file EnemyBullet.h
 * @brief 敵の弾
 */

#pragma once
#include "Object3d.h"
#include "Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

class EnemyBullet {
public:
	EnemyBullet();
	~EnemyBullet();

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
	void Initialize(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();

	/**
	 * @brief 更新
	*/
	bool IsDead() { return isDead_; };

private:
	Object3d* obj_ = nullptr;
	static Model* model_;

	int liveTimer_;
	Vector3 velocity_;
	int stayTime_;
	bool isDead_;

	BaseCollider* sphere_;
};
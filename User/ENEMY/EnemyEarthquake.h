/**
 * @file EnemyEarthquake.h
 * @brief 敵の地面攻撃
 */

#pragma once
#include"Object3d.h"
#include"Model.h"
#include"CollisionPrimitive.h"
#include"CollisionManager.h"

class Earthquake {
public:
	Earthquake();
	~Earthquake();

	///**
	// * @brief 静的初期化
	//*/
	//static void StaticInitialize();

	///**
	// * @brief 静的破棄
	//*/
	//static void StaticFinalize();

	/**
	 * @brief 初期化
	*/
	void Initialize(Vector3 createPos);

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

	bool attack();

private:
	Object3d* obj_ = nullptr;
	Model* model_;

	int timer_;
	int liveTime_;
	bool isDead_;

	float addSizeSpeed_;
	float maxSize_;
};

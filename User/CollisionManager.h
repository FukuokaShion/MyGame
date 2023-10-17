/**
 * @file CollisionManager.h
 * @brief 当たり判定のチェック
 */

#pragma once
#include"CollisionPrimitive.h"
#include<forward_list>
#include"Model.h"
#include"Object3d.h"

class CollisionManager {
public:
	~CollisionManager();

	/**
	 * @brief 初期化
	*/
	void Initialize();
	
	/**
	 * @brief インスタンス取得
	*/
	static CollisionManager* GetInstance();

	/**
	 * @brief 当たり判定登録
	*/
	void AddCollider(BaseCollider* collide);
	
	/**
	 * @brief 当たり判定解除
	*/
	void RemoveCollider(BaseCollider* collide);

	/**
	 * @brief 衝突チェック
	*/
	void CheakCol();
private:
	bool isPlayerHit;
	bool isEnemyHit;
	std::forward_list<BaseCollider*> colliders;

public://可視化関数
	/**
	 * @brief 当たり判定可視化
	*/
	void DrawCollider();

private://可視化変数
	Model* model_ = nullptr;
	int maxCol = 20;
	Object3d* objects_[20];
};
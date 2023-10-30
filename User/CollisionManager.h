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
	 * @brief デストラクタ
	*/
	void Finalize();

	/**
	 * @brief 衝突チェック
	*/
	void CheakCol();

	/**
	 * @brief プレイヤー攻撃判定
	*/
	void GetPlayerAttack(bool playerIsAttack);

	/**
	 * @brief 敵攻撃判定
	*/
	void GetEnemyAttack(bool enemyIsAttack);
	

private:
	bool isPlayerHit_;
	bool isEnemyHit_;
	std::forward_list<BaseCollider*> colliders_;


public://可視化関数
	/**
	 * @brief 当たり判定可視化
	*/
	void DrawCollider();

private://可視化変数
	Model* model_ = nullptr;
	int maxCol_ = 20;
	Object3d* objects_[20];
};
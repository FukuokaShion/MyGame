/**
 * @file ship.h
 * @brief タイトルシーン
 */

#pragma once
#include "Object3d.h"
#include"Input.h"

class Ship {
public:
	~Ship();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief obj描画
	*/
	void Draw();

	/**
	 * @brief 座標取得
	*/
	Vector3 GetPos() { return ship->wtf.position; };

private:
	//入力
	//Input* input_ = nullptr;

	//船
	Object3d* ship = nullptr;
	Model* shipMD = nullptr;
	float shipAngle;
	bool isMoveShip;
	float shipSpeed;
	int timer;
	int limit;

	//プレイヤー
	Object3d* player = nullptr;
	Model* playerMD = nullptr;

};
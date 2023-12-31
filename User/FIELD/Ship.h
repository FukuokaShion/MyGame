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
	 * @brief 動き始める
	*/
	void Start() { isMoveShip_ = true; };

	/**
	 * @brief 座標取得
	*/
	Vector3 GetPos() { return ship_->wtf.position; };

	/**
	 * @brief 動き始めているか取得
	*/
	bool GetIsMoveShip() { return isMoveShip_; };

private:
	//入力
	Input* input_ = nullptr;

	//船
	Object3d* ship_ = nullptr;
	Model* shipMD_ = nullptr;
	float shipAngle_;
	bool isMoveShip_;
	float shipSpeed_;
	int timer_;
	int limit_;

	//プレイヤー
	Object3d* player_ = nullptr;
	Model* playerMD_ = nullptr;

};
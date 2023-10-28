/**
 * @file Field.h
 * @brief ゲームシーンのステージ
 */

#pragma once
#include "Object3d.h"

class Field {
public:
	Field();
	~Field();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();
private:
	//背景や床
	Object3d* skydome_ = nullptr;
	Model* skydomeMD_ = nullptr;

	Object3d* floor_ = nullptr;
	Model* floorMD_ = nullptr;
	Object3d* water_ = nullptr;
	Model* waterMD_ = nullptr;

	Object3d* rock01_[3];
	Model* rock01MD_ = nullptr;
	Object3d* rock02_[3];
	Model* rock02MD_ = nullptr;

};
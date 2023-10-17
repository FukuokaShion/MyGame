/**
 * @file TitleField.h
 * @brief ゲームシーンのステージ
 */

#pragma once
#include "Object3d.h"

class TitleField {
public:
	TitleField();
	~TitleField();

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
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	Object3d* water = nullptr;
	Model* waterMD = nullptr;
	Object3d* coast = nullptr;
	Model* coastMD = nullptr;

	Object3d* rock01[2];
	Model* rock01MD = nullptr;
	Object3d* rock02[2];
	Model* rock02MD = nullptr;
};
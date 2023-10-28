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
	Object3d* skydome_ = nullptr;
	Model* skydomeMD_ = nullptr;
	Object3d* water_ = nullptr;
	Model* waterMD_ = nullptr;
	Object3d* coast_ = nullptr;
	Model* coastMD_ = nullptr;

	Object3d* rock01_[2];
	Model* rock01MD_ = nullptr;
	Object3d* rock02_[2];
	Model* rock02MD_ = nullptr;
};
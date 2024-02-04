/**
 * @file Option.h
 * @brief オプション画面
 */

#pragma once
#include"Sprite.h"
#include<memory>

class Option {
public:
	Option();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();

private:
	bool isChangeSensitivity_;
	float sensitivityChangeSpeed;

	std::unique_ptr<Sprite> basePic_;
	std::unique_ptr<Sprite> rPic_;
};
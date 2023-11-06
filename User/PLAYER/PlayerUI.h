/**
 * @file PlayerUI.h
 * @brief プレイヤーのUI管理クラス
 */
#pragma once
#include"Sprite.h"

class PlayerUI {
public:
	~PlayerUI();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update(int a,int b);

	/**
	 * @brief スプライト描画
	*/
	void Draw();

private:
	Sprite* hpGauge_;
	Sprite* damageGauge_;
	Sprite* base_;

};
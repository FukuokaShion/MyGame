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
	void Update(int damage,int hp);

	/**
	 * @brief スプライト描画
	*/
	void Draw();

private:
	Sprite* hpGauge_;
	Sprite* damageGauge_;
	Sprite* base_;

	const Vector4 hpColor_ = { 106.0f / 255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f };
	const Vector4 damageColor_ = { 255.0f / 255.0f,255.0f / 255.0f,3.0f / 255.0f,1.0f };

	const Vector2 hpGaugePos_ = { 128,38 };
	const Vector2 hpGaugeSize_ = { 400,26 };
	const int hpGaugeOneSize_ = 4;
};
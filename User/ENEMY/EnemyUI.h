/**
 * @file EnemyUI.h
 * @brief エネミーのUI管理クラス
 */
#pragma once
#include"Sprite.h"

class EnemyUI {
public:
	~EnemyUI();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update(int hp);

	/**
	 * @brief スプライト描画
	*/
	void Draw();

private:
	Sprite* enemyHpGauge_;
	Sprite* base_;

	const Vector2 hpGaugeSize = { 671,11 };
	const float hpGaugeOneSize = 0.671f;
};
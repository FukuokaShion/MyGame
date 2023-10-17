/**
 * @file SceneManager.h
 * @brief シーン管理
 */

#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"

class SceneManager{
public: // メンバ関数
	SceneManager();
	~SceneManager();

	/**
	 * @brief 初期化
	*/
	void Initialize(DirectXCommon* dxCommon);

	/**
	 * @brief シーン移行
	*/
	void TransitionTo(SceneState* state);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();
private: //メンバ変数 (固定)
	DirectXCommon* dxCommon_ = nullptr;

private:
	//シーン
	SceneState* state_ = nullptr;

};
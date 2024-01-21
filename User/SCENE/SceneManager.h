/**
 * @file SceneManager.h
 * @brief シーン管理
 */

#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"
#include "SceneChange.h"

class SceneManager {
public:
	enum class SCENE {
		TITLE,
		TUTORIAL,
		GAME,
	};

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
	void TransitionTo(SCENE nextScene);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();
private:
	void ChangeScene();

private: //メンバ変数 (固定)
	DirectXCommon* dxCommon_ = nullptr;

private:
	//シーン
	std::unique_ptr<SceneState> state_ = nullptr;
	SCENE nextScene_;
	std::unique_ptr<SceneChange> sceneChange_ = nullptr;
};
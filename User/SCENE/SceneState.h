#pragma once
#include "Input.h"

class SceneManager;

class SceneState {
public:
	//初期化
	SceneState();
	virtual void Initialize() = 0;
	virtual ~SceneState() = default;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void ObjectDraw() = 0;
	virtual void FbxDraw() = 0;
	virtual void SpriteDraw() = 0;

	//セッター
	static void SetSceneManager(SceneManager* sceneManager_) { sceneManager = sceneManager_; };
	static void SetInput(Input* input_) { input = input_; };

protected:
	//状態移行
	virtual void StateTransition() = 0;

protected:
	//シーンマネージャー
	static SceneManager* sceneManager;

	static Input* input;
};
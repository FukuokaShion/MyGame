/**
 * SceneManager.cpp
 * シーン管理
 */

#include "SceneManager.h"
#include"TitleScene.h"
#include"Object3d.h"
#include"FBXObject3d.h"

/// <summary>
/// コンストクラタ
/// </summary>
SceneManager::SceneManager() {
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager() {
	delete state_;
}

/// <summary>
/// 初期化
/// </summary>
void SceneManager::Initialize(DirectXCommon* dxCommon) {
	// nullチェック
	assert(dxCommon);
	this->dxCommon_ = dxCommon;

	//シーン初期
	SceneState::SetSceneManager(this);
	state_ = new TitleScene;
	state_->Initialize();
}

void SceneManager::TransitionTo(SceneState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
	state_->Initialize();
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void SceneManager::Update() {
	state_->Update();
}

/// <summary>
/// 描画
/// </summary>
void SceneManager::Draw() {
	///3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon_->GetCommandList());
	///3Dオブクジェクトの描画 
	state_->ObjectDraw();
	///3Dオブジェクト描画後処理
	Object3d::PostDraw();


	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon_->GetCommandList());
	///FBX描画
	state_->FbxDraw();
	///FBX描画後処理
	FBXObject3d::PostDraw();

	state_->SpriteDraw();
}
#include "SceneManager.h"
#include"TitleScene.h"
#include "FbxLoader.h"

/// <summary>
/// コンストクラタ
/// </summary>
SceneManager::SceneManager() {
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager() {
	delete spriteCommon;
	delete camera;

	delete state_;
}

/// <summary>
/// 初期化
/// </summary>
void SceneManager::Initialize(DirectXCommon* dxCommon) {
	// nullチェック
	assert(dxCommon);

	this->dxCommon = dxCommon;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);
	FBXObject3d::SetCamera(camera);

	//デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	//グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

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
	Object3d::PreDraw(dxCommon->GetCommandList());
	///3Dオブクジェクトの描画 
	state_->ObjectDraw();
	///3Dオブジェクト描画後処理
	Object3d::PostDraw();


	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon->GetCommandList());
	///FBX描画
	state_->FbxDraw();
	///FBX描画後処理
	FBXObject3d::PostDraw();

	state_->SpriteDraw();
}
#include "GameScene.h"
#include "FbxLoader.h"

/// <summary>
/// コンストクラタ
/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete field;
	delete camera;

	delete player;
	delete enemy;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//フィールド生成
	field = new Field();
	field->Initialize();

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

	//プレイヤー生成
	player = new Player();
	player->Initialize(input);
	player->SetCamera(camera);

	//エネミー生成
	enemy = new Enemy();
	enemy->Initialize();

	//カメラの設定
	camera->SetParent(player->GetWtf());
	camera->isSyncRota = false;

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	//仮の処理
	if (input->PushKey(DIK_SPACE)) {
		player->OnCollision(50);
	}

	//カメラ更新
	camera->Update();

	//オブジェクト更新
	field->Update();
	player->Update();
	enemy->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	field->Draw();
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon->GetCommandList());
	///FBX描画
	player->Draw();
	enemy->Draw();
	///FBX描画後処理
	FBXObject3d::PostDraw();


	//// パーティクルの描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	// パーティクル描画後処理
	ParticleManager::PostDraw();
}
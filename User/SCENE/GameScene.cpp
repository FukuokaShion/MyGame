﻿#include "GameScene.h"
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
	delete camera;

	delete floor;
	delete floorMD;
	delete skydome;
	delete skydomeMD;

	delete fbxObject3d_;
	delete fbxModel_;
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

	//背景
	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);
	floor->wtf.position = (Vector3{ 0, -10, 0 });

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	//fbx生成
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.rotation = { 0,PI,0 };
	animeSpeed = 1.0f;

	//カメラの設定
	camera->SetParent(&fbxObject3d_->wtf);
	camera->isSyncRota = true;

	Reset();
}

void GameScene::Reset() {

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	if(input->PushKey(DIK_D)){
		fbxObject3d_->wtf.position += {0.3f, 0, 0};
	}else if (input->PushKey(DIK_A)) {
		fbxObject3d_->wtf.position += {-0.3f, 0, 0};
	}
	
	if (input->PushKey(DIK_E)) {
		fbxObject3d_->wtf.rotation += {0, PI/180, 0};
	}else if (input->PushKey(DIK_Q)) {
		fbxObject3d_->wtf.rotation += {0, -PI/180, 0};
	}

	if (input->TriggerKey(DIK_SPACE)) {
		fbxObject3d_->PlayAnimation(animeSpeed, false);
	}

	//カメラ更新後にオブジェクト更新
	camera->Update();

	fbxObject3d_->Update();
	floor->Update();
	skydome->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	floor->Draw();
	skydome->Draw();
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon->GetCommandList());
	///FBX描画
	fbxObject3d_->Draw();
	///FBX描画後処理
	FBXObject3d::PostDraw();


	//// パーティクルの描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	// パーティクル描画後処理
	ParticleManager::PostDraw();
}
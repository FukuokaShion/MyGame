/**
 * @file Framework.cpp
 * @brief エンジンフレームワーク
 */

#include "Framework .h"
#include "Object3d.h"
#include "FBXObject3d.h"
#include "DirectionalLight.h"
#include "ParticleManager.h"
#include "GlobalVariables.h"

using namespace MyEngine;

void Framework::Initialize() {
	//windowsAPIの初期化
	winApp_ = new WinApp();
	winApp_->Initialize();

	dxCommon_ = new DirectXCommon();
	dxCommon_->Initialize(winApp_);

	//入力の初期化
	input_ = Input::GetInstance();
	input_->Initialize(winApp_);

	imGui_ = std::make_unique<ImGuiManager>();
	imGui_->Initialize(winApp_, dxCommon_);

	//fbx
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());
	FBXObject3d::SetDevice(dxCommon_->GetDevice());
	FBXObject3d::CreateGraphicsPipeline();
	
	//obj
	Object3d::StaticInitialize(dxCommon_->GetDevice());

	//ライト
	DirectionalLight::StaticInitialize(dxCommon_->GetDevice());

	//パーティクル
	ParticleManager::StaticInitialize(dxCommon_->GetDevice(), dxCommon_->GetCommandList());
	
	//スプライコモン
	SpriteCommon::SetDxCommon(dxCommon_);

	//調整項目
	GlobalVariables::GetInstance()->LoadFiles();

	//FPS固定
	fps_->SetFrameRate(60);
}

void  Framework::Finalize() {
	delete fps_;
	delete dxCommon_;
	imGui_->Finalize();
	FbxLoader::GetInstance()->Finalize();
	winApp_->Finalize();
}

void  Framework::Run() {
	//初期化
	Initialize();

	//ゲームループ
	while (true) {
		//ゲーム終了
		if (IsEndRequst()) {
			break;
		}

		//fps管理
		fps_->FpsControlBegin();

		imGui_->Begin();
		//更新処理
		Update();

		imGui_->End();
		//描画開始
		dxCommon_->PreDraw();
		//描画処理
		Draw();
		imGui_->Draw();
		//描画終了
		dxCommon_->PostDraw();

		//fps管理
		fps_->FpsControlEnd();
	}

	//破棄
	Finalize();
}


void  Framework::Update() {
	//入力の更新
	input_->Update();
#ifdef _DEBUG
	GlobalVariables::GetInstance()->Update();
#endif
}

void  Framework::Draw() {
}

bool  Framework::IsEndRequst() {
	if (winApp_->ProcessMessage()) {
		return true;
	}
	else if (input_->PushKey(DIK_ESCAPE)) {
		return true;
	}

	return false;
}
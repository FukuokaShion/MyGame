#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include <imgui.h>
#include "FbxLoader.h"
#include "FPS.h"

#include "GameScene.h"

#include"SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

#pragma region WindowsAPI初期化処理
	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;

	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化　
	input = new Input();
	input->Initialize(winApp);

	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	FBXObject3d::CreateGraphicsPipeline();

#pragma endregion

#pragma region DirectX初期化処理
	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//パーティクル静的初期化
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	SpriteCommon::SetDxCommon(dxCommon);
#pragma endregion

#pragma region 描画初期化処理
	//シーンの初期化
	SceneState::SetInput(input);
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Initialize(dxCommon);


	//FPS変えたいとき
	fps->SetFrameRate(60);

#pragma endregion
	//ゲームループ
	while (true) {
#pragma region ウィンドウメッセージ処理

		//アプリケーションが終わる時にmessageがWM_QUITになる
		if (winApp->ProcessMessage()) {
			break;
		}
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}

		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX毎フレーム処理
		//DireceX毎フレーム処理
		//入力の更新
		input->Update();	

		// ゲームシーンの毎フレーム処理
		sceneManager->Update();
#pragma endregion

#pragma region グラフィックスコマンド

		//描画コマンド
		dxCommon->PreDraw();

		//ゲームシーンの描画
		sceneManager->Draw();

		//描画終了
		dxCommon->PostDraw();

		fps->FpsControlEnd();

#pragma endregion

#pragma region 画面入れ替え

#pragma endregion
	}
#pragma region  WindowsAPI後始末
	delete sceneManager;

	FbxLoader::GetInstance()->Finalize();

	//WindowsAPIの終了処理
	winApp->Finalize();

	//入力開放
	delete input;
	//WindowsAPI開放
	delete winApp;
	delete dxCommon;

	delete fps;
	
#pragma endregion
	return 0;
}
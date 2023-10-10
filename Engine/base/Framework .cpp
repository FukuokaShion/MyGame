#include "Framework .h"
#include "Object3d.h"
#include "FBXObject3d.h"
#include "Sprite.h"
#include "ParticleManager.h"

void Framework::Initialize() {
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
	Object3d::StaticInitialize(dxCommon->GetDevice());

	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	SpriteCommon::SetDxCommon(dxCommon);

	//FPS固定
	fps->SetFrameRate(60);
}

void  Framework::Finalize() {
	delete fps;
	delete input;
	delete dxCommon;
	FbxLoader::GetInstance()->Finalize();
	winApp->Finalize();
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
		fps->FpsControlBegin();

		//更新処理
		Update();

		//描画開始
		dxCommon->PreDraw();
		//描画処理
		Draw();
		//描画終了
		dxCommon->PostDraw();

		//fps管理
		fps->FpsControlEnd();
	}

	//破棄
	Finalize();
}


void  Framework::Update() {
	//入力の更新
	input->Update();
}

void  Framework::Draw() {
}

bool  Framework::IsEndRequst() {
	if (winApp->ProcessMessage()) {
		return true;
	}
	else if (input->PushKey(DIK_ESCAPE)) {
		return true;
	}

	return false;
}
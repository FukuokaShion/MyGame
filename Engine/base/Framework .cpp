#include "Framework .h"
#include "Object3d.h"
#include "FBXObject3d.h"
#include "Sprite.h"
#include "ParticleManager.h"

void Framework::Initialize() {
	//windowsAPI‚Ì‰Šú‰»
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//“ü—Í‚Ì‰Šú‰»
	input = new Input();
	input->Initialize(winApp);

	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	FBXObject3d::CreateGraphicsPipeline();
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	SpriteCommon::SetDxCommon(dxCommon);

	//FPSŒÅ’è
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
	//‰Šú‰»
	Initialize();

	//ƒQ[ƒ€ƒ‹[ƒv
	while (true) {
		//ƒQ[ƒ€I—¹
		if (IsEndRequst()) {
			break;
		}

		//fpsŠÇ—
		fps->FpsControlBegin();

		//XVˆ—
		Update();

		//•`‰æŠJŽn
		dxCommon->PreDraw();
		//•`‰æˆ—
		Draw();
		//•`‰æI—¹
		dxCommon->PostDraw();
		
		//fpsŠÇ—
		fps->FpsControlEnd();
	}

	//”jŠü
	Finalize();
}


void  Framework::Update() {
	//“ü—Í‚ÌXV
	input->Update();
}

void  Framework::Draw() {
}

bool  Framework::IsEndRequst() {
	if (winApp->ProcessMessage()) {
		return true;
	}else if (input->PushKey(DIK_ESCAPE)) {
		return true;
	}

	return false;
}
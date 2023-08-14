#include "Framework .h"
#include "Object3d.h"
#include "FBXObject3d.h"
#include "Sprite.h"
#include "ParticleManager.h"

void Framework::Initialize() {
	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	FBXObject3d::CreateGraphicsPipeline();
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	SpriteCommon::SetDxCommon(dxCommon);

	//FPS�Œ�
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
	//������
	Initialize();

	//�Q�[�����[�v
	while (true) {
		//�Q�[���I��
		if (IsEndRequst()) {
			break;
		}

		//fps�Ǘ�
		fps->FpsControlBegin();

		//�X�V����
		Update();

		//�`��J�n
		dxCommon->PreDraw();
		//�`�揈��
		Draw();
		//�`��I��
		dxCommon->PostDraw();
		
		//fps�Ǘ�
		fps->FpsControlEnd();
	}

	//�j��
	Finalize();
}


void  Framework::Update() {
	//���͂̍X�V
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
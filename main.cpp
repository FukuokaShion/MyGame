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

#pragma region WindowsAPI����������
	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;

	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏������@
	input = new Input();
	input->Initialize(winApp);

	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	FBXObject3d::CreateGraphicsPipeline();

#pragma endregion

#pragma region DirectX����������
	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	SpriteCommon::SetDxCommon(dxCommon);
#pragma endregion

#pragma region �`�揉��������
	//�V�[���̏�����
	SceneState::SetInput(input);
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Initialize(dxCommon);


	//FPS�ς������Ƃ�
	fps->SetFrameRate(60);

#pragma endregion
	//�Q�[�����[�v
	while (true) {
#pragma region �E�B���h�E���b�Z�[�W����

		//�A�v���P�[�V�������I��鎞��message��WM_QUIT�ɂȂ�
		if (winApp->ProcessMessage()) {
			break;
		}
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}

		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX���t���[������
		//DireceX���t���[������
		//���͂̍X�V
		input->Update();	

		// �Q�[���V�[���̖��t���[������
		sceneManager->Update();
#pragma endregion

#pragma region �O���t�B�b�N�X�R�}���h

		//�`��R�}���h
		dxCommon->PreDraw();

		//�Q�[���V�[���̕`��
		sceneManager->Draw();

		//�`��I��
		dxCommon->PostDraw();

		fps->FpsControlEnd();

#pragma endregion

#pragma region ��ʓ���ւ�

#pragma endregion
	}
#pragma region  WindowsAPI��n��
	delete sceneManager;

	FbxLoader::GetInstance()->Finalize();

	//WindowsAPI�̏I������
	winApp->Finalize();

	//���͊J��
	delete input;
	//WindowsAPI�J��
	delete winApp;
	delete dxCommon;

	delete fps;
	
#pragma endregion
	return 0;
}
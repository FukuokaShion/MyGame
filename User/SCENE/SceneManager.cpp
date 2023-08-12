#include "SceneManager.h"
#include"TitleScene.h"
#include "FbxLoader.h"

/// <summary>
/// �R���X�g�N���^
/// </summary>
SceneManager::SceneManager() {
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager() {
	delete spriteCommon;
	delete camera;

	delete state_;
}

/// <summary>
/// ������
/// </summary>
void SceneManager::Initialize(DirectXCommon* dxCommon) {
	// null�`�F�b�N
	assert(dxCommon);

	this->dxCommon = dxCommon;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	//�J�����Z�b�g
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);
	FBXObject3d::SetCamera(camera);

	//�f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	//�O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();

	SceneState::SetSceneManager(this);
	state_ = new TitleScene;
	state_->Initialize();
}

void SceneManager::TransitionTo(SceneState* state) {
	//�폜
	delete state_;
	//�V�K�쐬
	state_ = state;
	state_->Initialize();
}

/// <summary>
/// ���t���[������
/// </summary>
void SceneManager::Update() {
	state_->Update();
}

/// <summary>
/// �`��
/// </summary>
void SceneManager::Draw() {
	///3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	///3D�I�u�N�W�F�N�g�̕`�� 
	state_->ObjectDraw();
	///3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();


	///fbx�`��O����
	FBXObject3d::PreDraw(dxCommon->GetCommandList());
	///FBX�`��
	state_->FbxDraw();
	///FBX�`��㏈��
	FBXObject3d::PostDraw();

	state_->SpriteDraw();
}
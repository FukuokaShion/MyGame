#pragma once
#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "Matrix4.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include "Audio.h"

#include "Camera.h"
#include "Object3d.h"
#include "Model.h"
#include "FBXObject3d.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class SceneManager
{
private: // �ÓI�����o�ϐ�

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	SceneManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SceneManager();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon);

	//��Ԉڍs
	void TransitionTo(SceneState* state);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private: //�����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

private:
	//�J����
	Camera* camera = nullptr;

	//�V�[��
	SceneState* state_ = nullptr;
	
};
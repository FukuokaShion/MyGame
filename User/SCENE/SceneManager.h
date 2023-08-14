#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"

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
private: //�����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;

private:
	//�V�[��
	SceneState* state_ = nullptr;
	
};
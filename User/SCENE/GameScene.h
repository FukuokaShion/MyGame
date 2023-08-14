#pragma once
#include"SceneState.h"
#include"Sprite.h"

#include"Field.h"
#include"Player.h"
#include"Enemy.h"

class GameScene : public SceneState {
public:
	GameScene();
	void Initialize();
	~GameScene();

	//�X�V
	void Update() override;

	//�`��
	void ObjectDraw() override;
	void FbxDraw() override;
	void SpriteDraw() override;

private:
	void StateTransition() override;

private:
	//�摜
	SpriteCommon* spriteCommon = nullptr;

	//�����o�ϐ�
	//�J����
	Camera* camera = nullptr;
	//�t�B�[���h
	Field* field = nullptr;

	//�v���C���[
	Player* player = nullptr;
	//�G�l�~�[
	Enemy* enemy = nullptr;

	//�摜
	Sprite* UIBase;

	Sprite* hpGauge;
	Sprite* enemyHpGauge;
};

/*
/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �ÓI�����o�ϐ�

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

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
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

	const float PI = 3.141592f;

private:
	enum class Scene{
		Titele,
		Option,
		Game,
		Clear,
		GAmeOver,
	};
	Scene scene;
	
	
	//�����o�ϐ�
	//�J����
	Camera* camera = nullptr;
	//�t�B�[���h
	Field* field = nullptr;

	//�v���C���[
	Player* player = nullptr;
	//�G�l�~�[
	Enemy* enemy = nullptr;

	//�摜
	Sprite* titlePic;
	Sprite* clearPic;
	Sprite* gameoverPic;

	Sprite* UIBase;

	Sprite* hpGauge;
	Sprite* enemyHpGauge;
};*/
#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"

#include"Field.h"
#include"Player.h"
#include"Enemy.h"
#include"CollisionManager.h"

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
	//�T�E���h
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice = nullptr;

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
	Sprite* damageGauge;
	Sprite* enemyHpGauge;

	CollisionManager* collisionManager = nullptr;
};
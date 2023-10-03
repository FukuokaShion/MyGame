#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include "Object3d.h"
#include"Audio.h"

class TitleScene : public SceneState {
public:
	TitleScene();
	void Initialize();
	~TitleScene();
	
	//�X�V
	void Update() override;

	//�`��
	void ObjectDraw() override;
	void FbxDraw() override;
	void SpriteDraw() override;

private:
	void StateTransition() override;
	
private:
	//�T�E���h
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice = nullptr;

	//�J����
	Camera* camera = nullptr;

	//�摜
	SpriteCommon* spriteCommon = nullptr;
	Sprite* basePic;
	std::unique_ptr<Sprite> black;

	//obj
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	Object3d* water = nullptr;
	Model* waterMD = nullptr;
	Object3d* coast = nullptr;
	Model* coastMD = nullptr;

	Object3d* rock01[2];
	Model* rock01MD = nullptr;
	Object3d* rock02[2];
	Model* rock02MD = nullptr;

	//�D
	Object3d* ship = nullptr;
	Model* shipMD = nullptr;
	float shipAngle;
	bool isMoveShip;
	float shipSpeed;
	int timer;
	int limit;

	//�v���C���[
	Object3d* player = nullptr;
	Model* playerMD = nullptr;
};
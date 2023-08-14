#pragma once
#include "Input.h"

class SceneManager;

class SceneState {
public:
	//������
	SceneState();
	virtual void Initialize() = 0;
	virtual ~SceneState() = default;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void ObjectDraw() = 0;
	virtual void FbxDraw() = 0;
	virtual void SpriteDraw() = 0;

	//�Z�b�^�[
	static void SetSceneManager(SceneManager* sceneManager_) { sceneManager = sceneManager_; };
	static void SetInput(Input* input_) { input = input_; };

protected:
	//��Ԉڍs
	virtual void StateTransition() = 0;

protected:
	//�V�[���}�l�[�W���[
	static SceneManager* sceneManager;

	static Input* input;
};
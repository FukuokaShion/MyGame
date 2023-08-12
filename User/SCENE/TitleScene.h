#pragma once
#include"SceneState.h"
#include"Sprite.h"

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
	//�摜
	SpriteCommon* spriteCommon = nullptr;
	Sprite* basePic;
};
#pragma once
#include"SceneState.h"
#include"Sprite.h"

class TitleScene : public SceneState {
public:
	TitleScene();
	void Initialize();
	~TitleScene();
	
	//XV
	void Update() override;

	//•`‰æ
	void ObjectDraw() override;
	void FbxDraw() override;
	void SpriteDraw() override;

private:
	void StateTransition() override;
	
private:
	//‰æ‘œ
	SpriteCommon* spriteCommon = nullptr;
	Sprite* basePic;
};
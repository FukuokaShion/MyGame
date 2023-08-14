#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"

TitleScene::TitleScene() {
}

void TitleScene::Initialize() {

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	basePic = new Sprite();
	basePic->Initialize(spriteCommon);
	basePic->SetPozition({ 0,0 });
	basePic->SetSize({ 1280,720 });

	spriteCommon->LoadTexture(0, "title.png");
	basePic->SetTextureIndex(0);
}

TitleScene::~TitleScene() {
	delete basePic;
	delete spriteCommon;
}

//更新
void TitleScene::Update() {
	StateTransition();
}


void TitleScene::ObjectDraw() {
}

void TitleScene::FbxDraw() {
}

void TitleScene::SpriteDraw() {
	basePic->Draw();
}

void TitleScene::StateTransition() {
	if (input->PButtonTrigger(B)) {
		sceneManager->TransitionTo(new GameScene);
	}
}
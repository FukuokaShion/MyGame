/**
 * @file TitleScene.cpp
 * @brief タイトルシーン
 */

#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"

TitleScene::TitleScene() {
}

void TitleScene::Initialize() {
	//サウンド
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("ocean.wav");

	pSourceVoice = audio->PlayWave("ocean.wav");

	float PI = 3.1415f;
	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	camera->wtf.position = { 0,6,-7 };
	camera->wtf.rotation = { 10 * PI / 180.0f , -25 * PI / 180.0f,0 };

	Object3d::SetCamera(camera);

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	basePic = new Sprite();
	basePic->Initialize(spriteCommon);
	basePic->SetPozition({ 0,0 });
	basePic->SetSize({ 1280,720 });

	black = std::make_unique<Sprite>();
	black->Initialize(spriteCommon);
	black->SetPozition({ 0,0 });
	black->SetSize({ 1280,720 });
	black->SetColor({ 0,0,0,0 });

	loading = std::make_unique<Sprite>();
	loading->Initialize(spriteCommon);
	loading->SetPozition({ 0,0 });
	loading->SetSize({ 1280,720 });
	
	spriteCommon->LoadTexture(0, "title.png");
	basePic->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "white.png");
	black->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "loading.png");
	loading->SetTextureIndex(2);
	
	field = std::make_unique<TitleField>();
	field->Initialize();

	ship = std::make_unique<Ship>();
	ship->Initialize();
}

TitleScene::~TitleScene() {
	delete basePic;
	delete spriteCommon;
	audio->StopWave(pSourceVoice);
}

//更新
void TitleScene::Update() {
	camera->Update();
	field->Update();
	ship->Update();
	StateTransition();
}


void TitleScene::ObjectDraw() {
	field->Draw();
	ship->Draw();
}

void TitleScene::FbxDraw() {

}

void TitleScene::SpriteDraw() {
	basePic->Draw();
	black->Draw();
	if (black->GetColor().w >= 1.0f) {
		loading->Draw();
	}
}

void TitleScene::StateTransition() {
	if (ship->GetPos().z > 60.0f) {
		black->SetColor({ 0,0,0,black->GetColor().w + 0.04f });
	}

	if (ship->GetPos().z > 120) {
		sceneManager->TransitionTo(new GameScene);
	}
}
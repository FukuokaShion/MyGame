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
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("ocean.wav");

	pSourceVoice_ = audio_->PlayWave("ocean.wav");

	float PI = 3.1415f;
	// カメラ生成
	camera_ = new Camera(WinApp::window_width, WinApp::window_height);
	camera_->wtf.position = { 0,6,-7 };
	camera_->wtf.rotation = { 10 * PI / 180.0f , -25 * PI / 180.0f,0 };

	Object3d::SetCamera(camera_);

	basePic_ = new Sprite();
	basePic_->Initialize(SpriteCommon::GetInstance());
	basePic_->SetPozition({ 0,0 });
	basePic_->SetSize({ 1280,720 });

	black_ = std::make_unique<Sprite>();
	black_->Initialize(SpriteCommon::GetInstance());
	black_->SetPozition({ 0,0 });
	black_->SetSize({ 1280,720 });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(SpriteCommon::GetInstance());
	loading_->SetPozition({ 0,0 });
	loading_->SetSize({ 1280,720 });
	
	basePic_->SetTextureIndex(1);
	black_->SetTextureIndex(0);
	loading_->SetTextureIndex(2);
	
	field_ = std::make_unique<TitleField>();
	field_->Initialize();

	ship_ = std::make_unique<Ship>();
	ship_->Initialize();
}

TitleScene::~TitleScene() {
	delete basePic_;
	audio_->StopWave(pSourceVoice_);
}

//更新
void TitleScene::Update() {
	camera_->Update();
	field_->Update();
	ship_->Update();

	basePic_->Update();
	black_->Update();
	loading_->Update();
	StateTransition();
}


void TitleScene::ObjectDraw() {
	field_->Draw();
	ship_->Draw();
}

void TitleScene::FbxDraw() {

}

void TitleScene::SpriteDraw() {
	basePic_->Draw();
	black_->Draw();
	if (black_->GetColor().w >= 1.0f) {
		loading_->Draw();
	}
}

void TitleScene::StateTransition() {
	if (ship_->GetPos().z > 60.0f) {
		black_->SetColor({ 0,0,0,black_->GetColor().w + 0.04f });
	}

	if (ship_->GetPos().z > 120) {
		sceneManager_->TransitionTo(new GameScene);
	}
}
/**
 * @file TitleScene.cpp
 * @brief タイトルシーン
 */

#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"
#include"SpriteLoader.h"

TitleScene::TitleScene() {
}

void TitleScene::Initialize() {
	//サウンド
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("ocean.wav");

	pSourceVoice_ = audio_->PlayWave("ocean.wav");

	const float PI = 3.1415f;
	// カメラ生成
	camera_ = new Camera();
	camera_->Initialize(WinApp::window_width, WinApp::window_height);
	camera_->wtf.position = { 0.0f,6.0f,-7.0f };
	const Vector3 camDegree = { 10.0f,-25.0f,0.0f };
	camera_->wtf.rotation = { camDegree.x * PI / 180.0f , camDegree.y * PI / 180.0f,camDegree.z * PI / 180.0f };

	Object3d::SetCamera(camera_);

	basePic_ = new Sprite();
	basePic_->Initialize(SpriteCommon::GetInstance());
	basePic_->SetSize({ WinApp::window_width,WinApp::window_height });

	black_ = std::make_unique<Sprite>();
	black_->Initialize(SpriteCommon::GetInstance());
	black_->SetSize({ WinApp::window_width,WinApp::window_height });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(SpriteCommon::GetInstance());
	loading_->SetSize({ WinApp::window_width,WinApp::window_height });
	
	basePic_->SetTextureIndex(SpriteLoader::TITLE);
	black_->SetTextureIndex(SpriteLoader::WHITE);
	loading_->SetTextureIndex(SpriteLoader::LOADING);
	
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
	if (ship_->GetPos().z > blackDrawPos) {
		black_->SetColor({ 0,0,0,black_->GetColor().w + blackAddAlpha });
	}

	if (ship_->GetPos().z > shipMoveEnd) {
		sceneManager_->TransitionTo(new GameScene);
	}
}
/**
 * @file Option.cpp
 * @brief オプション画面
 */

#include"Option.h"
#include"SpriteLoader.h"
#include"Input.h"
#include"GameCamera.h"

Option::Option() {}

void Option::Initialize() {
	isChangeSensitivity_ = false;
	sensitivityChangeSpeed = 0.0005f;

	basePic_ = std::make_unique<Sprite>();
	basePic_->Initialize(SpriteCommon::GetInstance());
	basePic_->SetSize({ WinApp::window_width,WinApp::window_height });
	basePic_->SetTextureIndex(SpriteLoader::OPTION);

	rPic_ = std::make_unique<Sprite>();
	rPic_->Initialize(SpriteCommon::GetInstance());
	rPic_->SetSize({ 48,48 });
	rPic_->SetAnchorPoint({ 0.5f,0.5f });
	rPic_->SetPozition({ 405 + (GameCamera::GetSensitivity().x - 0.02f) * 8880.0f, 521.0f });
	rPic_->SetTextureIndex(SpriteLoader::RSTICK);
}

void Option::Update() {
	basePic_->Update();
	rPic_->SetPozition({ 405 + (GameCamera::GetSensitivity().x - 0.02f) * 8880.0f, 521.0f });
	rPic_->Update();

	if (0 < Input::GetInstance()->GetRightStickVec().x) {	
		GameCamera::ChangeSensitivity({ sensitivityChangeSpeed,0});

	}else if (Input::GetInstance()->GetRightStickVec().x < 0) {
		GameCamera::ChangeSensitivity({ -sensitivityChangeSpeed,0 });

	}
}

void Option::SpriteDraw() {
	basePic_->Draw();
	rPic_->Draw();
}
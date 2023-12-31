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

	startSelect_ = { 1185,327 };
	optionSelect_ = { 1185,490 };
	arrow_ = new Sprite();
	arrow_->Initialize(SpriteCommon::GetInstance());
	arrow_->SetPozition(startSelect_);
	arrow_->SetSize({ 64,64 });


	basePic_->SetTextureIndex(SpriteLoader::TITLE);
	arrow_->SetTextureIndex(SpriteLoader::ARROW);

	field_ = std::make_unique<TitleField>();
	field_->Initialize();

	ship_ = std::make_unique<Ship>();
	ship_->Initialize();

	option_ = new Option();
	option_->Initialize();
	optionOpen_ = false;
	isStartSelect_ = true;
}

TitleScene::~TitleScene() {
	delete basePic_;
	delete arrow_;
	delete option_;
	audio_->StopWave(pSourceVoice_);
}

//更新
void TitleScene::Update() {
	if (optionOpen_) {
		//オプション画面
		option_->Update();
		if (Input::GetInstance()->PButtonTrigger(B) || Input::GetInstance()->PButtonTrigger(START)) {
			optionOpen_ = false;
		}
	}else {
		//スタート画面
		if (ship_->GetIsMoveShip() == false) {
			//選択変更
			if (Input::GetInstance()->LeftStickInput()) {
				if (Input::GetInstance()->GetLeftStickVec().y > 0) {
					arrow_->SetPozition(startSelect_);
					isStartSelect_ = true;
				}else if (Input::GetInstance()->GetLeftStickVec().y < 0) {
					arrow_->SetPozition(optionSelect_);
					isStartSelect_ = false;
				}
			}
			//実行
			if (Input::GetInstance()->PButtonTrigger(B)) {
				if (isStartSelect_) {
					ship_->Start();
				}else {
					optionOpen_ = true;
				}
			}
		}

		camera_->Update();
		field_->Update();
		ship_->Update();
		basePic_->Update();
		arrow_->Update();
		StateTransition();
	}

}


void TitleScene::ObjectDraw() {
	field_->Draw();
	ship_->Draw();
}

void TitleScene::FbxDraw() {

}

void TitleScene::SpriteDraw() {
	if (optionOpen_) {
		option_->SpriteDraw();
	}
	else {
		basePic_->Draw();
		arrow_->Draw();
	}
}

void TitleScene::StateTransition() {
	if (fadeOutPos < ship_->GetPos().z) {
		sceneManager_->TransitionTo(SceneManager::SCENE::GAME);
	}
}
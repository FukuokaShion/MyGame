/**
 * @file GameScene.cpp
 * @brief チュートリアルシーン
 */

#include"TutorialScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
#include"Easing.h"
#include"Collision.h"
#include"ParticleManager.h"

TutorialScene::TutorialScene() {
}

void TutorialScene::Initialize() {
	// カメラ生成
	gameCamera_ = make_unique<GameCamera>();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(gameCamera_.get());
	Object3d::SetCamera(gameCamera_.get());
	FBXObject3d::SetCamera(gameCamera_.get());
	state_ = State::game;

	//フィールド生成
	field_ = std::make_unique<TutorialField>();
	field_->Initialize();

	//プレイヤー生成
	player_ = make_unique<Player>();
	player_->Initialize();

	//カメラの設定
	gameCamera_->SetParentPos(player_->GetWtf().position);

	//サウンド
	audio_ = make_unique<Audio>();
	audio_->Initialize();
	audio_->LoadWave("game.wav");

	pSourceVoice_ = audio_->PlayWave("game.wav");
	pSourceVoice_->SetVolume(0.8f);

	//画像
	pushB_ = std::make_unique<Sprite>();
	pushB_->Initialize(SpriteCommon::GetInstance());
	pushB_->SetSize({ 200,48 });
	pushB_->SetPozition({ 1050,650 });
	pushB_->Update();
	pushB_->SetTextureIndex(SpriteLoader::PUSHB);

	CollisionManager::GetInstance()->Initialize();

	option_ = make_unique<Option>();
	option_->Initialize();
}

TutorialScene::~TutorialScene() {
	CollisionManager::GetInstance()->Finalize();
}

//更新
void TutorialScene::Update() {
	Vector3 distance;
	Vector3 pushVelocity;

	//オブジェクト更新
	field_->SetPlayerPos(player_->GetWtf().position);
	field_->Update();

	switch (state_) {
	case State::game:
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->SetRockOnPos(field_->GetScarecrowTargetPos());
		gameCamera_->Update();


		player_->SetCamViewVec(gameCamera_->GetViewVec());
		player_->Update();

		//押し出し処理
		if (Collision::CircleCollisionXZ(player_->GetWtf().position, field_->GetScarecrowPos(), player_->GetRad(), 1.3f)) {
			distance = player_->GetWtf().position - field_->GetScarecrowPos();
			distance.y = 0;
			pushVelocity = distance;
			pushVelocity.nomalize();
			pushVelocity *= player_->GetRad() + 1.3f;
			pushVelocity -= distance;
			player_->Move(pushVelocity);
		}

		CollisionManager::GetInstance()->GetPlayerAttack(player_->GetIsAttack());
		CollisionManager::GetInstance()->CheakCol();

		if (Input::GetInstance()->PButtonTrigger(START)) {
			state_ = State::option;
		}

		break;
	case State::option:
		option_->Update();
		if (Input::GetInstance()->PButtonTrigger(START)) {
			state_ = State::game;
		}

		break;
	}
}


void TutorialScene::ObjectDraw() {
	field_->ObjDraw();
	CollisionManager::GetInstance()->DrawCollider();
}

void TutorialScene::FbxDraw() {
	player_->Draw();
}

void TutorialScene::SpriteDraw() {
	switch (state_) {
	case State::game:
		player_->DrawSprite();
		field_->SpriteDraw();
		break;
	case State::option:
		option_->SpriteDraw();

		break;
	}
}

void TutorialScene::StateTransition() {
	if (player_->IsLive() == false) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}
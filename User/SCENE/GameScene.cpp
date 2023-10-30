/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include"GameScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"
#include"Easing.h"

GameScene::GameScene() {
}

void GameScene::Initialize() {
	//スプライト共通部分の初期化
	spriteCommon_ = new SpriteCommon;
	spriteCommon_->Initialize();

	// カメラ生成
	camera_ = new Camera(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(camera_);
	Object3d::SetCamera(camera_);
	FBXObject3d::SetCamera(camera_);

	state_ = State::game;

	//フィールド生成
	field_ = new Field();
	field_->Initialize();


	//エネミー生成
	enemy_ = new Enemy();
	enemy_->Initialize();

	//プレイヤー生成
	player_ = new Player();
	player_->Initialize();
	player_->SetCamera(camera_);


	//カメラの設定
	camera_->SetParent(player_->GetWtfP());
	camera_->isSyncRota = false;

	//サウンド
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("game.wav");

	pSourceVoice_ = audio_->PlayWave("game.wav");
	pSourceVoice_->SetVolume(0.8f);

	//スプライト
	UIBase_ = new Sprite();
	UIBase_->Initialize(spriteCommon_);
	UIBase_->SetPozition({ 0,0 });
	UIBase_->SetSize({ 1280,720 });

	hpGauge_ = new Sprite();
	hpGauge_->Initialize(spriteCommon_);
	hpGauge_->SetPozition({ 128,38 });
	hpGauge_->SetSize({ 400,26 });
	hpGauge_->SetColor({ 106.0f / 255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f });

	damageGauge_ = new Sprite();
	damageGauge_->Initialize(spriteCommon_);
	damageGauge_->SetPozition({ 128,38 });
	damageGauge_->SetSize({ 400,26 });
	damageGauge_->SetColor({ 255.0f / 255.0f,255.0f / 255.0f,3.0f / 255.0f,1.0f });

	enemyHpGauge_ = new Sprite();
	enemyHpGauge_->Initialize(spriteCommon_);
	enemyHpGauge_->SetPozition({ 309,576 });
	enemyHpGauge_->SetSize({ 671,11 });
	enemyHpGauge_->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });

	clear_ = new Sprite();
	clear_->Initialize(spriteCommon_);
	clear_->SetPozition({ 0,0 });
	clear_->SetSize({ 1280,720 });

	gameOver_ = new Sprite();
	gameOver_->Initialize(spriteCommon_);
	gameOver_->SetPozition({ 0,0 });
	gameOver_->SetSize({ 1280,720 });

	spriteCommon_->LoadTexture(0, "UIBase.png");
	UIBase_->SetTextureIndex(0);
	spriteCommon_->LoadTexture(1, "white.png");
	hpGauge_->SetTextureIndex(1);
	spriteCommon_->LoadTexture(2, "white.png");
	damageGauge_->SetTextureIndex(2);
	spriteCommon_->LoadTexture(3, "white.png");
	enemyHpGauge_->SetTextureIndex(3);
	spriteCommon_->LoadTexture(4, "clear.png");
	clear_->SetTextureIndex(4);
	spriteCommon_->LoadTexture(5, "gameOver.png");
	gameOver_->SetTextureIndex(5);

	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Initialize();
}

GameScene::~GameScene() {
	delete spriteCommon_;
	delete camera_;
	delete audio_;

	delete field_;

	delete player_;
	delete enemy_;

	delete UIBase_;
	delete hpGauge_;
	delete damageGauge_;
	delete enemyHpGauge_;
	delete clear_;
	delete gameOver_;
}

//更新
void GameScene::Update() {
	switch (state_) {
	case State::game:
		//オブジェクト更新
		field_->Update();
		player_->Update();
		enemy_->Update(player_->GetWtf().position);
		collisionManager_->GetPlayerAttack(player_->GetIsAttack());
		collisionManager_->GetEnemyAttack(enemy_->GetIsAttack());
		collisionManager_->CheakCol();

		damageGauge_->SetSize({ static_cast<float>(4 * player_->GetDamage()),26 });
		hpGauge_->SetSize({ static_cast<float>(4 * player_->GetHp()),26 });
		enemyHpGauge_->SetSize({ static_cast<float>(6.71f * enemy_->GetHp()),11 });

		if (enemy_->IsLive() == false) {
			state_ = State::clear;
		}
		else if (player_->IsLive() == false) {
			state_ = State::death;
		}
		break;
	case State::clear:
		if (input_->PButtonTrigger(B)) {
			sceneManager_->TransitionTo(new TitleScene);
		}
		break;
	case State::death:
		if (input_->PButtonTrigger(B)) {
			sceneManager_->TransitionTo(new TitleScene);
		}
		break;
	}
}


void GameScene::ObjectDraw() {
	field_->Draw();
	collisionManager_->DrawCollider();
	enemy_->ObjDraw();
}

void GameScene::FbxDraw() {
	player_->Draw();
	enemy_->Draw();
}

void GameScene::SpriteDraw() {
	switch (state_) {
	case State::game:
		UIBase_->Draw();
		damageGauge_->Draw();
		hpGauge_->Draw();
		enemyHpGauge_->Draw();

		break;
	case State::clear:

		clear_->Draw();
		break;
	case State::death:

		gameOver_->Draw();
		break;
	}
}

void GameScene::StateTransition() {
	if (enemy_->IsLive() == false) {
		sceneManager_->TransitionTo(new TitleScene);
	}
	else if (player_->IsLive() == false) {
		sceneManager_->TransitionTo(new TitleScene);
	}
}
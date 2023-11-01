/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include"GameScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"
#include"Easing.h"
#include"Collision.h"

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
	UiBase_ = new Sprite();
	UiBase_->Initialize(spriteCommon_);
	UiBase_->SetPozition({ 0,0 });
	UiBase_->SetSize({ 1280,720 });

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
	gameOver_->SetColor({ 1,1,1,0 });

	black_ = std::make_unique<Sprite>();
	black_->Initialize(spriteCommon_);
	black_->SetPozition({ 0,0 });
	black_->SetSize({ 1280,720 });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(spriteCommon_);
	loading_->SetPozition({ 0,0 });
	loading_->SetSize({ 1280,720 });

	spriteCommon_->LoadTexture(0, "UI.png");
	UiBase_->SetTextureIndex(0);

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

	spriteCommon_->LoadTexture(6, "white.png");
	black_->SetTextureIndex(6);
	
	spriteCommon_->LoadTexture(7, "loading.png");
	loading_->SetTextureIndex(7);

	isGameOver = false;

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

	delete UiBase_;
	delete hpGauge_;
	delete damageGauge_;
	delete enemyHpGauge_;
	delete clear_;
	delete gameOver_;

	collisionManager_->Finalize();
}

//更新
void GameScene::Update() {

	Vector3 distance;
	Vector3 pushVelocity;

	//オブジェクト更新
	field_->Update();
	enemy_->Update(player_->GetWtf().position);

	switch (state_) {
	case State::game:
		player_->Update();
		//押し出し処理
		if (Collision::CircleCollision(player_->GetWtf().position, enemy_->GetWtf().position, 0.4f, 1.3f)) {
			distance = player_->GetWtf().position - enemy_->GetWtf().position;
			pushVelocity = distance;
			pushVelocity.nomalize();
			pushVelocity *= 0.4f + 1.3f;
			pushVelocity -= distance;
			player_->Move(pushVelocity);
		}

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
		gameOver_->SetColor({ 1,1,1,gameOver_->GetColor().w + 0.01f });

		if (gameOver_->GetColor().w >= 0.6f) {
			if (input_->PButtonTrigger(B)) {
				isGameOver = true;
			}
		}
		if (isGameOver) {
			black_->SetColor({ 0,0,0,black_->GetColor().w + 0.04f });
			if (black_->GetColor().w >= 1.0f) {
				sceneManager_->TransitionTo(new TitleScene);
			}
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
		UiBase_->Draw();
		damageGauge_->Draw();
		hpGauge_->Draw();
		enemyHpGauge_->Draw();

		break;
	case State::clear:

		clear_->Draw();
		break;
	case State::death:
		black_->Draw();
		if (black_->GetColor().w >= 0.9f) {
			loading_->Draw();
		}else{
			gameOver_->Draw();
		}
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
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

	clear_ = new Sprite();
	clear_->Initialize(SpriteCommon::GetInstance());
	clear_->SetPozition({ 0,0 });
	clear_->SetSize({ 1280,720 });
	clear_->SetColor({1,1,1,0});
	clear_->Update();

	gameOver_ = new Sprite();
	gameOver_->Initialize(SpriteCommon::GetInstance());
	gameOver_->SetPozition({ 0,0 });
	gameOver_->SetSize({ 1280,720 });
	gameOver_->SetColor({ 1,1,1,0 });

	black_ = std::make_unique<Sprite>();
	black_->Initialize(SpriteCommon::GetInstance());
	black_->SetPozition({ 0,0 });
	black_->SetSize({ 1280,720 });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(SpriteCommon::GetInstance());
	loading_->SetPozition({ 0,0 });
	loading_->SetSize({ 1280,720 });

	
	clear_->SetTextureIndex(5);
	gameOver_->SetTextureIndex(6);
	black_->SetTextureIndex(0);
	loading_->SetTextureIndex(2);

	isGameOver = false;

	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Initialize();
}

GameScene::~GameScene() {
	delete camera_;
	delete audio_;

	delete field_;

	delete player_;
	delete enemy_;

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


		if (enemy_->IsLive() == false) {
			state_ = State::clear;
		}
		else if (player_->IsLive() == false) {
			state_ = State::death;
		}
		break;
	case State::clear:
		//クリア画面
		player_->Update();
		clear_->Update();
		if (clear_->GetColor().w < 1.0f) {
			clear_->SetColor({ 1,1,1,clear_->GetColor().w + 0.005f});

		}else if (clear_->GetColor().w >= 1.0f) {
			if (input_->PButtonTrigger(B)) {
				sceneManager_->TransitionTo(new TitleScene);
			}
		}
		break;
	case State::death:
		//ゲームオーバー画面
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
		player_->DrawSprite();
		enemy_->SpriteDraw();

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
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
	gameCamera_ = new GameCamera();
	gameCamera_->Initialize(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(gameCamera_);
	Object3d::SetCamera(gameCamera_);
	FBXObject3d::SetCamera(gameCamera_);

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

	//カメラの設定
	gameCamera_->SetParentPos(player_->GetWtf().position);

	//サウンド
	audio_ = new Audio();
	audio_->Initialize();
	audio_->LoadWave("game.wav");

	pSourceVoice_ = audio_->PlayWave("game.wav");
	pSourceVoice_->SetVolume(0.8f);

	clear_ = new Sprite();
	clear_->Initialize(SpriteCommon::GetInstance());
	clear_->SetSize({ WinApp::window_width,WinApp::window_height });
	clear_->SetColor({1,1,1,0});
	clear_->Update();

	gameOver_ = new Sprite();
	gameOver_->Initialize(SpriteCommon::GetInstance());
	gameOver_->SetSize({ WinApp::window_width,WinApp::window_height });
	gameOver_->SetColor({ 1,1,1,0 });

	black_ = std::make_unique<Sprite>();
	black_->Initialize(SpriteCommon::GetInstance());
	black_->SetSize({ WinApp::window_width,WinApp::window_height });
	black_->SetColor({ 0,0,0,0 });

	loading_ = std::make_unique<Sprite>();
	loading_->Initialize(SpriteCommon::GetInstance());
	loading_->SetSize({ WinApp::window_width,WinApp::window_height });

	
	clear_->SetTextureIndex(5);
	gameOver_->SetTextureIndex(6);
	black_->SetTextureIndex(0);
	loading_->SetTextureIndex(2);

	isGameOver = false;

	collisionManager_ = CollisionManager::GetInstance();
	collisionManager_->Initialize();

	option_ = new Option();
	option_->Initialize();
}

GameScene::~GameScene() {
	delete gameCamera_;
	delete audio_;

	delete field_;

	delete player_;
	delete enemy_;

	delete clear_;
	delete gameOver_;

	delete option_;

	collisionManager_->Finalize();
}

//更新
void GameScene::Update() {
	Vector3 distance;
	Vector3 pushVelocity;

	//オブジェクト更新
	field_->Update();

	switch (state_) {
	case State::game:
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->Update();

		enemy_->Update(player_->GetWtf().position);

		player_->SetCamViewVec(gameCamera_->GetViewVec());
		player_->Update();
		//押し出し処理
		if (Collision::CircleCollision(player_->GetWtf().position, enemy_->GetWtf().position, player_->GetRad(), enemy_->GetRad())) {
			distance = player_->GetWtf().position - enemy_->GetWtf().position;
			pushVelocity = distance;
			pushVelocity.nomalize();
			pushVelocity *= player_->GetRad() + enemy_->GetRad();
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


		if (Input::GetInstance()->PButtonTrigger(START)) {
			state_ = State::option;
		}

		break;
	case State::clear:
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->Update();

		enemy_->Update(player_->GetWtf().position);

		//クリア画面
		player_->Update();
		clear_->Update();
		if (clear_->GetColor().w < 1.0f) {
			clear_->SetColor({ 1,1,1,clear_->GetColor().w + clearAddAlpha_});

		}else if (clear_->GetColor().w >= 1.0f) {
			if (input_->PButtonTrigger(B)) {
				sceneManager_->TransitionTo(new TitleScene);
			}
		}
		break;
	case State::death:
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->Update();

		enemy_->Update(player_->GetWtf().position);

		loading_->Update();
		gameOver_->Update();
		//ゲームオーバー画面
		gameOver_->SetColor({ 1,1,1,gameOver_->GetColor().w + gameOverAddAlpha_ });

		if (gameOver_->GetColor().w >= gameOverAlphaEnd_) {
			if (input_->PButtonTrigger(B)) {
				isGameOver = true;
			}
		}
		if (isGameOver) {
			black_->SetColor({ 0,0,0,black_->GetColor().w + blackAddAlpha_ });
			if (black_->GetColor().w >= 1.0f) {
				sceneManager_->TransitionTo(new TitleScene);
			}
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
		if (black_->GetColor().w >= 1.0f) {
			loading_->Draw();
		}else{
			gameOver_->Draw();
		}
		break;
	case State::option:
		option_->SpriteDraw();

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
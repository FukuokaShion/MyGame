/**
 * @file GameScene.cpp
 * @brief ゲームプレイシーン
 */

#include"GameScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"
#include"SpriteLoader.h"
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

	//画像
	telopBase_ = new Sprite();
	telopBase_->Initialize(SpriteCommon::GetInstance());
	telopBase_->SetSize({ WinApp::window_width,WinApp::window_height });
	telopBase_->SetColor({ 1,1,1,0 });
	telopBase_->Update();
	telopBaseAddAlpha_ = 0.04f;

	pushB_ = new Sprite();
	pushB_->Initialize(SpriteCommon::GetInstance());
	pushB_->SetSize({ 200,48 });
	pushB_->SetPozition({1050,650});
	pushB_->Update();

	clear_ = new Sprite();
	clear_->Initialize(SpriteCommon::GetInstance());
	clear_->SetSize({ WinApp::window_width,WinApp::window_height });
	clear_->SetColor({1,1,1,0});
	clear_->Update();

	clearEffect_ = new Sprite();
	clearEffect_->Initialize(SpriteCommon::GetInstance());
	clearEffect_->SetAnchorPoint({ 0.5f,0 });
	clearEffect_->SetPozition({ 1280 / 2,0 });
	clearEffect_->SetSize({ WinApp::window_width,WinApp::window_height });
	clearEffect_->SetColor({ 1.6f,1.6f,1.6f,0.5f });
	clearEffect_->Update();
	clearEffAddSize_ = 2;
	clearEffSubtractAlpha_ = -0.005f;

	youDiedPic_ = new Sprite();
	youDiedPic_->Initialize(SpriteCommon::GetInstance());
	youDiedPic_->SetSize({ WinApp::window_width,WinApp::window_height });
	youDiedPic_->SetColor({ 1,1,1,0 });
	youDiedAddAlpha_ = 0.01f;

	telopBase_->SetTextureIndex(SpriteLoader::TELOPBASE);
	pushB_->SetTextureIndex(SpriteLoader::PUSHA);
	clear_->SetTextureIndex(SpriteLoader::BOSSFELLED);
	clearEffect_->SetTextureIndex(SpriteLoader::BOSSFELLED);
	youDiedPic_->SetTextureIndex(SpriteLoader::YOUDIED);

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

	delete telopBase_;
	delete pushB_;
	delete clear_;
	delete clearEffect_;
	delete youDiedPic_;

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
		enemy_->Update(player_->GetWtf().position);

		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->SetRockOnPos(enemy_->GetCenterPos());
		gameCamera_->Update();


		player_->SetCamViewVec(gameCamera_->GetViewVec());
		player_->Update();

		//押し出し処理
		if (Collision::CircleCollisionXZ(player_->GetWtf().position, enemy_->GetWtf().position, player_->GetRad(), enemy_->GetRad())) {
			distance = player_->GetWtf().position - enemy_->GetWtf().position;
			distance.y = 0;
			pushVelocity = distance;
			pushVelocity.nomalize();
			pushVelocity *= player_->GetRad() + enemy_->GetRad();
			pushVelocity -= distance;
			player_->Move(pushVelocity);
		}

		//地震仮ダメージ判定
		if (enemy_->JISIN) {
			if (Collision::CircleCollisionXZ(player_->GetWtf().position, enemy_->GetWtf().position, player_->GetRad(), 8)) {
				if (player_->Damage(180)) {
					enemy_->JISIN = false;
				}
			}
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
		//クリア画面
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->Update();

		player_->Update();
		enemy_->Update(player_->GetWtf().position);

		telopBase_->Update();
		pushB_->Update();
		clear_->Update();
		clearEffect_->Update();

		clearEffect_->SetSize({ clearEffect_->GetSize().x + clearEffAddSize_,WinApp::window_height });
		clearEffect_->SetColor({ 1, 1, 1, clearEffect_->GetColor().w + clearEffSubtractAlpha_ });

		if (telopBase_->GetColor().w <= 1.0f) {
			telopBase_->SetColor({ 1, 1, 1, telopBase_->GetColor().w + telopBaseAddAlpha_ });
			clear_->SetColor({ 1,1,1,clear_->GetColor().w + telopBaseAddAlpha_ });
		}

		if (clear_->GetColor().w >= 1.0f) {
			if (input_->PButtonTrigger(A)) {
				sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
			}
		}

		break;
	case State::death:
		//ゲームオーバー画面
		gameCamera_->SetParentPos(player_->GetWtf().position);
		gameCamera_->SetParentViewVec(player_->GetWtf().rotation);
		gameCamera_->Update();

		enemy_->Update(player_->GetWtf().position);

		if (telopBase_->GetColor().w <= 1.0f) {
			telopBase_->SetColor({ 1, 1, 1, telopBase_->GetColor().w + telopBaseAddAlpha_ });
		}
		if (youDiedPic_->GetColor().w < 1.0f) {
			youDiedPic_->SetColor({ 1, 1, 1, youDiedPic_->GetColor().w + youDiedAddAlpha_ });
		}else if (youDiedPic_->GetColor().w >= 1.0f) {
			if(Input::GetInstance()->PButtonTrigger(A)){
				sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
			}
		}

		telopBase_->Update();
		pushB_->Update();
		youDiedPic_->Update();
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
		telopBase_->Draw();
		clearEffect_->Draw();
		clear_->Draw();
		pushB_->Draw();
		break;
	case State::death:
		telopBase_->Draw();
		youDiedPic_->Draw();
		pushB_->Draw();
		break;
	case State::option:
		option_->SpriteDraw();

		break;
	}
}

void GameScene::StateTransition() {
	if (enemy_->IsLive() == false) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
	else if (player_->IsLive() == false) {
		sceneManager_->TransitionTo(SceneManager::SCENE::TITLE);
	}
}
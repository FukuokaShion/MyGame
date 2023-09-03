#include"GameScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"
#include"Easing.h"

GameScene::GameScene() {
}

void GameScene::Initialize() {
	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);
	FBXObject3d::SetCamera(camera);

	state = State::game;

	//フィールド生成
	field = new Field();
	field->Initialize();


	//エネミー生成
	enemy = new Enemy();
	enemy->Initialize();
	CollisionManager::SetEnemy(enemy);

	//プレイヤー生成
	player = new Player();
	player->Initialize(input);
	player->SetCamera(camera);
	CollisionManager::SetPlayer(player);


	//カメラの設定
	camera->SetParent(player->GetWtfP());
	camera->isSyncRota = false;

	//サウンド
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("bb.wav");

	pSourceVoice = audio->PlayWave("bb.wav");
	pSourceVoice->SetVolume(0.03f);

	//スプライト
	UIBase = new Sprite();
	UIBase->Initialize(spriteCommon);
	UIBase->SetPozition({ 0,0 });
	UIBase->SetSize({ 1280,720 });

	hpGauge = new Sprite();
	hpGauge->Initialize(spriteCommon);
	hpGauge->SetPozition({ 128,38 });
	hpGauge->SetSize({ 400,26 });
	hpGauge->SetColor({ 106.0f / 255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f });

	damageGauge = new Sprite();
	damageGauge->Initialize(spriteCommon);
	damageGauge->SetPozition({ 128,38 });
	damageGauge->SetSize({ 400,26 });
	damageGauge->SetColor({ 255.0f / 255.0f,255.0f / 255.0f,3.0f / 255.0f,1.0f });

	enemyHpGauge = new Sprite();
	enemyHpGauge->Initialize(spriteCommon);
	enemyHpGauge->SetPozition({ 309,576 });
	enemyHpGauge->SetSize({ 671,11 });
	enemyHpGauge->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });

	clear = new Sprite();
	clear->Initialize(spriteCommon);
	clear->SetPozition({ 0,0 });
	clear->SetSize({ 1280,720 });

	gameOver = new Sprite();
	gameOver->Initialize(spriteCommon);
	gameOver->SetPozition({ 0,0 });
	gameOver->SetSize({ 1280,720 });

	spriteCommon->LoadTexture(0, "UIBase.png");
	UIBase->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "white.png");
	hpGauge->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "white.png");
	damageGauge->SetTextureIndex(2);
	spriteCommon->LoadTexture(3, "white.png");
	enemyHpGauge->SetTextureIndex(3);
	spriteCommon->LoadTexture(4, "clear.png");
	clear->SetTextureIndex(4);
	spriteCommon->LoadTexture(5, "gameOver.png");
	gameOver->SetTextureIndex(5);

	collisionManager = CollisionManager::GetInstance();
}

GameScene::~GameScene() {
	delete spriteCommon;
	delete camera;
	delete audio;

	delete field;

	delete player;
	delete enemy;

	delete UIBase;
	delete hpGauge;
	delete damageGauge;
	delete enemyHpGauge;
	delete clear;
	delete gameOver;
}

//更新
void GameScene::Update() {
	switch (state) {
	case State::game:
		//オブジェクト更新
		field->Update();
		player->Update();
		enemy->Update(player->GetWtf().position);
		CollisionManager::CheckCollision();
		collisionManager->CheakCol();

		damageGauge->SetSize({ static_cast<float>(4 * player->GetDamage()),26 });
		hpGauge->SetSize({ static_cast<float>(4 * player->GetHp()),26 });
		enemyHpGauge->SetSize({ static_cast<float>(6.71f * enemy->GetHp()),11 });

		if (enemy->IsLive() == false) {
			state = State::clear;
		}
		else if (player->IsLive() == false) {
			state = State::death;
		}
		break;
	case State::clear:
		if (input->PButtonTrigger(B)) {
			sceneManager->TransitionTo(new TitleScene);
		}
		break;
	case State::death:
		if (input->PButtonTrigger(B)) {
			sceneManager->TransitionTo(new TitleScene);
		}
		break;
	}
}


void GameScene::ObjectDraw() {
	field->Draw();
	enemy->ObjDraw();
}

void GameScene::FbxDraw() {
	player->Draw();
	enemy->Draw();
}

void GameScene::SpriteDraw() {
	switch (state) {
	case State::game:
		UIBase->Draw();
		damageGauge->Draw();
		hpGauge->Draw();
		enemyHpGauge->Draw();

		break;
	case State::clear:

		clear->Draw();
		break;
	case State::death:

		gameOver->Draw();
		break;
	}
}

void GameScene::StateTransition() {
	if (enemy->IsLive() == false) {
		sceneManager->TransitionTo(new TitleScene);
	}
	else if (player->IsLive() == false) {
		sceneManager->TransitionTo(new TitleScene);
	}
}
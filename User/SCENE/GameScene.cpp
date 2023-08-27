#include"GameScene.h"
#include"SceneManager.h"
#include"TitleScene.h"

#include"FbxLoader.h"

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

	//フィールド生成
	field = new Field();
	field->Initialize();

	//プレイヤー生成
	player = new Player();
	player->Initialize(input);
	player->SetCamera(camera);
	CollisionManager::SetPlayer(player);

	//エネミー生成
	enemy = new Enemy();
	enemy->Initialize();
	enemy->SetPlayerTransform(player->GetWtfP());
	CollisionManager::SetEnemy(enemy);

	//カメラの設定
	camera->SetParent(player->GetWtfP());
	camera->isSyncRota = false;

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

	enemyHpGauge = new Sprite();
	enemyHpGauge->Initialize(spriteCommon);
	enemyHpGauge->SetPozition({ 309,576 });
	enemyHpGauge->SetSize({ 671,11 });
	enemyHpGauge->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });


	spriteCommon->LoadTexture(0, "UIBase.png");
	UIBase->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "white.png");
	hpGauge->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "white.png");
	enemyHpGauge->SetTextureIndex(2);

	collisionManager = CollisionManager::GetInstance();
}

GameScene::~GameScene() {
	delete spriteCommon;
	delete camera;

	delete field;

	delete player;
	delete enemy;

	delete UIBase;
	delete hpGauge;
	delete enemyHpGauge;
}

//更新
void GameScene::Update() {
	//オブジェクト更新
	field->Update();
	player->Update();
	enemy->Update();
	CollisionManager::CheckCollision();
	collisionManager->CheakCol();

	hpGauge->SetSize({ static_cast<float>(4 * player->GetHp()),26 });
	enemyHpGauge->SetSize({ static_cast<float>(6.71f * enemy->GetHp()),11 });

	StateTransition();
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
	UIBase->Draw();
	hpGauge->Draw();
	enemyHpGauge->Draw();
}

void GameScene::StateTransition() {
	if (enemy->IsLive() == false) {
		sceneManager->TransitionTo(new TitleScene);
	}
	else if (player->IsLive() == false) {
		sceneManager->TransitionTo(new TitleScene);
	}
}
#include "GameScene.h"
#include "FbxLoader.h"

/// <summary>
/// コンストクラタ
/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete field;
	delete camera;

	delete player;
	delete enemy;

	delete titlePic;
	delete clearPic;
	delete gameoverPic;

	delete UIBase;
	delete hpGauge;
	delete enemyHpGauge;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//フィールド生成
	field = new Field();
	field->Initialize();

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	//カメラセット
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);
	FBXObject3d::SetCamera(camera);

	//デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	//グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

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

	scene = Scene::Titele;

	titlePic = new Sprite();
	titlePic->Initialize(spriteCommon);
	titlePic->SetPozition({ 0,0 });
	titlePic->SetSize({ 1280,720 });

	clearPic = new Sprite();
	clearPic->Initialize(spriteCommon);
	clearPic->SetPozition({ 0,0 });
	clearPic->SetSize({ 1280,720 });

	gameoverPic = new Sprite();
	gameoverPic->Initialize(spriteCommon);
	gameoverPic->SetPozition({ 0,0 });
	gameoverPic->SetSize({ 1280,720 });

	UIBase = new Sprite();
	UIBase->Initialize(spriteCommon);
	UIBase->SetPozition({ 0,0 });
	UIBase->SetSize({ 1280,720 });

	hpGauge = new Sprite();
	hpGauge->Initialize(spriteCommon);
	hpGauge->SetPozition({ 128,38 });
	hpGauge->SetSize({ 400,26 });
	hpGauge->SetColor({ 106.0f/255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f });

	enemyHpGauge = new Sprite();
	enemyHpGauge->Initialize(spriteCommon);
	enemyHpGauge->SetPozition({ 309,576 });
	enemyHpGauge->SetSize({ 671,11 });
	enemyHpGauge->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });

	spriteCommon->LoadTexture(0, "title.png");
	titlePic->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "clear.png");
	clearPic->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "gameOver.png");
	gameoverPic->SetTextureIndex(2);

	spriteCommon->LoadTexture(3, "UIBase.png");
	UIBase->SetTextureIndex(3);
	spriteCommon->LoadTexture(4, "white.png");
	hpGauge->SetTextureIndex(4);
	spriteCommon->LoadTexture(5, "white.png");
	enemyHpGauge->SetTextureIndex(5);

}


/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {

	switch (scene) {
	case Scene::Titele:
		if (input->PButtonTrigger(B)) {
			scene = Scene::Game;
			player->Initialize(input);
			enemy->Initialize();
			camera->wtf.Initialize();
		}


		break;
	case Scene::Option:
		if (input->PButtonTrigger(B)) {
			scene = Scene::Titele;
		}

		break;
	case Scene::Game:
		//オブジェクト更新
		field->Update();
		player->Update();
		enemy->Update();
		CollisionManager::CheckCollision();

		hpGauge->SetSize({ static_cast<float>(4 * player->GetHp()),26 });
		enemyHpGauge->SetSize({ static_cast<float>(6.71f * enemy->GetHp()),11 });


		if (enemy->IsLive() == false) {
			scene = Scene::Clear;
		}else if (player->IsLive() == false) {
			scene = Scene::GAmeOver;
		}

		break;
	case Scene::Clear:
		if (input->PButtonTrigger(B)) {
			scene = Scene::Titele;
		}

		break;
	case Scene::GAmeOver:
		if (input->PButtonTrigger(B)) {
			scene = Scene::Titele;
		}

		break;
	}



}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	switch (scene) {
	case Scene::Titele:

		break;
	case Scene::Option:

		break;
	case Scene::Game:
		field->Draw();

		break;
	case Scene::Clear:

		break;
	case Scene::GAmeOver:

		break;
	}
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	///fbx描画前処理
	FBXObject3d::PreDraw(dxCommon->GetCommandList());
	///FBX描画
	switch (scene) {
	case Scene::Titele:

		break;
	case Scene::Option:

		break;
	case Scene::Game:
		player->Draw();
		enemy->Draw();
		
		break;
	case Scene::Clear:

		break;
	case Scene::GAmeOver:

		break;
	}
	///FBX描画後処理
	FBXObject3d::PostDraw();

	switch (scene) {
	case Scene::Titele:
		titlePic->Draw();


		break;
	case Scene::Option:

		break;
	case Scene::Game:
		UIBase->Draw();
		hpGauge->Draw();
		enemyHpGauge->Draw();

		break;
	case Scene::Clear:
		clearPic->Draw();
		
		break;
	case Scene::GAmeOver:
		gameoverPic->Draw();

		break;
	}
}
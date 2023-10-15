/**
 * @file TitleScene.cpp
 * @brief タイトルシーン
 */

#include"TitleScene.h"
#include"SceneManager.h"
#include"GameScene.h"


#include"Easing.h"

TitleScene::TitleScene() {
}

void TitleScene::Initialize() {
	//サウンド
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("ocean.wav");

	pSourceVoice = audio->PlayWave("ocean.wav");

	float PI = 3.1415f;
	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	camera->wtf.position = { 0,6,-7 };
	camera->wtf.rotation = { 10 * PI / 180.0f , -25 * PI / 180.0f,0 };

	Object3d::SetCamera(camera);

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize();

	basePic = new Sprite();
	basePic->Initialize(spriteCommon);
	basePic->SetPozition({ 0,0 });
	basePic->SetSize({ 1280,720 });

	black = std::make_unique<Sprite>();
	black->Initialize(spriteCommon);
	black->SetPozition({ 0,0 });
	black->SetSize({ 1280,720 });
	black->SetColor({ 0,0,0,0 });

	spriteCommon->LoadTexture(0, "title.png");
	basePic->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "white.png");
	black->SetTextureIndex(1);

	//obj
	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	waterMD = Model::LoadFromOBJ("water");
	water = Object3d::Create();
	water->SetModel(waterMD);
	water->wtf.scale = { 2,1,2 };

	coastMD = Model::LoadFromOBJ("coast");
	coast = Object3d::Create();
	coast->SetModel(coastMD);
	coast->wtf.scale = { 2,1,2 };
	coast->wtf.rotation.y = 3.14f;

	rock01MD = Model::LoadFromOBJ("rock01");
	rock02MD = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 2; i++) {
		rock01[i] = Object3d::Create();
		rock01[i]->SetModel(rock01MD);
		rock02[i] = Object3d::Create();
		rock02[i]->SetModel(rock02MD);
	}

	rock01[0]->wtf.position = { -50,0,240 };
	rock01[0]->wtf.scale = { 1.4f,1,1 };
	rock01[0]->wtf.rotation = { 0,0,0 };

	rock01[1]->wtf.position = { -60,0,250 };
	rock01[1]->wtf.scale = { 1,1.3f,1.2f };
	rock01[1]->wtf.rotation = { 0,PI / 2,0 };

	rock02[0]->wtf.position = { -70,0,250 };
	rock02[0]->wtf.scale = { 2,2,2 };
	rock02[0]->wtf.rotation = { 0,0,0 };

	rock02[1]->wtf.position = { -40,0,240 };
	rock02[1]->wtf.scale = { 1.5f,1.5f,1.5f };
	rock02[1]->wtf.rotation = { 0,220 * PI / 180,0 };

	shipMD = Model::LoadFromOBJ("ship");
	ship = Object3d::Create();
	ship->SetModel(shipMD);
	ship->wtf.position = { -20,0,28 };
	shipAngle = 0.04f * 3.141592f / 180.0f;
	shipSpeed = 0.3f;
	timer = 0;
	limit = 90;

	playerMD = Model::LoadFromOBJ("playerObj");
	player = Object3d::Create();
	player->SetModel(playerMD);
	player->wtf.position = { -20,0.5f,28 };
}

TitleScene::~TitleScene() {
	delete basePic;
	delete spriteCommon;

	delete skydome;
	delete skydomeMD;
	delete water;
	delete waterMD;
	delete coast;
	delete coastMD;
	for (int i = 0; i < 2; i++) {
		delete rock01[i];
		delete rock02[i];
	}

	delete rock01MD;
	delete rock02MD;

	delete ship;
	delete shipMD;

	delete player;
	delete playerMD;

	audio->StopWave(pSourceVoice);
}

//更新
void TitleScene::Update() {
	camera->Update();
	skydome->Update();
	water->Update();
	coast->Update();

	if (abs(ship->wtf.rotation.x) > 4 * 3.141592f / 180) {
		shipAngle *= -1;
	}
	ship->wtf.rotation.x += shipAngle;

	ship->Update();
	for (int i = 0; i < 2; i++) {
		rock01[i]->Update();
		rock02[i]->Update();
	}

	player->Update();

	StateTransition();
}


void TitleScene::ObjectDraw() {
	skydome->Draw();
	player->Draw();
	ship->Draw();
	water->Draw();
	coast->Draw();
	for (int i = 0; i < 2; i++) {
		rock01[i]->Draw();
		rock02[i]->Draw();
	}
}

void TitleScene::FbxDraw() {

}

void TitleScene::SpriteDraw() {
	basePic->Draw();
	black->Draw();
}

void TitleScene::StateTransition() {
	if (input->TriggerKey(DIK_SPACE)) {
		isMoveShip = true;
	}

	if (isMoveShip) {
		if (timer < limit) {
			timer++;
		}

		float t = static_cast<float>(timer) / static_cast<float>(limit);

		float add = Easing::OutQuad(0, shipSpeed, t);

		ship->wtf.position.z += add;
		player->wtf.position.z += add;
	}

	if (ship->wtf.position.z > 60.0f) {
		black->SetColor({ 0,0,0,black->GetColor().w + 0.04f });
	}

	if (ship->wtf.position.z > 120) {
		sceneManager->TransitionTo(new GameScene);
	}
}
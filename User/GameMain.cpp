/**
 * @file GameMain.cpp
 * @brief ゲーム全体の流れ
 */

#include "GameMain.h"

GameMain::GameMain() {
}

GameMain::~GameMain() {
}

void GameMain::Initialize() {
	Framework::Initialize();
	//シーンの初期化
	sceneManager = new SceneManager();
	sceneManager->Initialize(dxCommon);

	//読み込み
	loader = new LoaderManager();
	loader->Initilize();
	loader->Load();
}

void GameMain::Finalize() {
	delete sceneManager;
	loader->Finalize();

	Framework::Finalize();
}

void GameMain::Update() {
	Framework::Update();

	sceneManager->Update();
}

void GameMain::Draw() {
	Framework::Draw();

	sceneManager->Draw();
}

bool GameMain::IsEndRequst() {
	return Framework::IsEndRequst();
}
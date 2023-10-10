#include "GameMain.h"

GameMain::GameMain() {
}

GameMain::~GameMain() {
}

void GameMain::Initialize() {
	Framework::Initialize();

	//シーンの初期化
	SceneState::SetInput(input);
	sceneManager = new SceneManager();
	sceneManager->Initialize(dxCommon);
}

void GameMain::Finalize() {
	delete sceneManager;

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
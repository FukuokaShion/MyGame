#include "Player.h"
#include "FbxLoader.h"

Player::Player() {
	//ƒ‚ƒfƒ‹¶¬
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
}

Player::~Player() {
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Update() {
	fbxObject3d_->Update();


}

void Player::Draw() {
	//fbxObject3d_->Draw();
}
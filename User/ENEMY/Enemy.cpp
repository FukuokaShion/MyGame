#include "Enemy.h"
#include "FbxLoader.h"
#include"Standby.h"
#include"EnemyAttack.h"

Enemy::Enemy() {
	//ƒ‚ƒfƒ‹¶¬
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);

}

void Enemy::Initialize() {
	action = new Action(new EnemyAttack);
	action->SetTransform(&fbxObject3d_->wtf);
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;

}

void Enemy::Update() {
	action->Update();
	fbxObject3d_->Update();

}

void Enemy::Draw() {
	fbxObject3d_->Draw();

}
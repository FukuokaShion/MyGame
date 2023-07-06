#include "Enemy.h"
#include "FbxLoader.h"
#include"Standby.h"
#include"EnemyAttack.h"

Enemy::Enemy() {
	//ƒ‚ƒfƒ‹¶¬
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemystand");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);

}

void Enemy::Initialize() {
	action = new Action(new Standby);
	action->SetTransform(&fbxObject3d_->wtf);
	fbxObject3d_->wtf.position = { 0,0,8 };
	fbxObject3d_->PlayAnimation();
}

void Enemy::SetPlayerTransform(Transform* playerWtf) {
	action->SetPlayerTransform(playerWtf);
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
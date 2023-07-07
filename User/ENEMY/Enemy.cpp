#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"

Enemy::Enemy() {
	//ƒ‚ƒfƒ‹¶¬
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemystand");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	
	hp = new EnemyHp();
}

void Enemy::Initialize() {
	action = new EnemyAction(new EnemyStandby);
	action->SetTransform(&fbxObject3d_->wtf);
	fbxObject3d_->wtf.position = { 0,0,8 };
	fbxObject3d_->PlayAnimation();
	hp->Initialize();
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

void Enemy::OnCollision(int damage) {
	hp->Damage(damage);
}

void Enemy::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
}
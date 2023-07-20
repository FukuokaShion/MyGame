#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"

Enemy::Enemy() {
	//���f������
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemystand");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	
	hp = new EnemyHp();

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 5.0f;

	attackHitBox.radius = 3.0f;

	isAttack = false;
	power = 0;
}

void Enemy::Initialize() {
	TransitionTo(new Standby);

	fbxObject3d_->wtf.position = { 0,0,8 };
	fbxObject3d_->PlayAnimation();
	hp->Initialize();

}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp;
	delete state_;
}

void Enemy::Update() {
	//�����蔻��X�V
	bodyHitBox.center = fbxObject3d_->wtf.position;
	attackHitBox.center = fbxObject3d_->wtf.position;
	state_->Update();
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

//��Ԃ�ύX����
void Enemy::TransitionTo(EnemyState* state) {
	//�폜
	delete state_;
	//�V�K�쐬
	state_ = state;
	state_->SetEnemy(this);
}
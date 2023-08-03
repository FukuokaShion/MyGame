#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"

Enemy::Enemy() {
	//モデル生成
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemy");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	
	hp = new EnemyHp();

	isAttack = false;
	power = 0;

	state_->SetEnemy(this);

	particle = new EnemyParticle;
}

void Enemy::Initialize() {
	TransitionTo(new Standby);
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.position = { 0,0,8 };
	hp->Initialize();

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 3.0f;
	bodyHitBox.radius = 1.7f;

	attackHitBox.radius = 3.0f;

	isAttack = false;
	power = 0;
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp;
	delete state_;
	delete particle;
}

void Enemy::Update() {
	//当たり判定更新
	bodyHitBox.center = fbxObject3d_->wtf.position;
	attackHitBox.center = fbxObject3d_->wtf.position;
	state_->Update();
	fbxObject3d_->Update();
	particle->Update();
}

void Enemy::OnCollision(int damage, Vector3 hitPos) {
	hp->Damage(damage);
	particle->OnColision(hitPos);
}

void Enemy::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
	particle->Draw();
}

//状態を変更する
void Enemy::TransitionTo(EnemyState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
}
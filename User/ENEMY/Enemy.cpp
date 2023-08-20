#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyShooting.h"

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
	EnemyBullet::StaticInitialize();
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp;
	delete state_;
	delete particle;
	bullets.clear();
	EnemyBullet::StaticFinalize();
}

void Enemy::Update() {
	//当たり判定
	bodyHitBox.center = fbxObject3d_->wtf.position;
	attackHitBox.center = fbxObject3d_->wtf.position;

	//行動
	state_->Update();
	
	//オブジェクト
	fbxObject3d_->Update();

	//弾
	bullets.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
	for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
		bullet->Update();
	}

	//パーティクル
	particle->Update();
}

void Enemy::OnCollision(int damage, Vector3 hitPos) {
	hp->Damage(damage);
	particle->OnColision(hitPos);
}

void Enemy::Draw() {
	fbxObject3d_->Draw();
}

void Enemy::ObjDraw() {
	for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
		bullet->Draw();
	}
	particle->Draw();
}

void Enemy::CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit) {
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos,velocity,liveLimit);
	bullets.push_back(std::move(newBullet));
}

//状態を変更する
void Enemy::TransitionTo(EnemyState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
}
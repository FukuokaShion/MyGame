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

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 5.0f;

	attackHitBox.radius = 3.0f;

	isAttack = false;
	power = 0;

	state_->SetEnemy(this);
}

void Enemy::Initialize() {
	TransitionTo(new Standby);
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.Initialize();
	fbxObject3d_->wtf.position = { 0,0,8 };
	hp->Initialize();

	bodyHitBox.center = fbxObject3d_->wtf.position;
	bodyHitBox.height = 5.0f;

	attackHitBox.radius = 3.0f;

	isAttack = false;
	power = 0;


	//パーティクル生成
	DamageParticle = std::make_unique<ParticleManager>();
	DamageParticle.get()->Initialize();
	DamageParticle->LoadTexture("blod.png");
	DamageParticle->Update();
}

Enemy::~Enemy() {
	delete fbxObject3d_;
	delete fbxModel_;
	delete hp;
	delete state_;
}

void Enemy::Update() {
	//当たり判定更新
	bodyHitBox.center = fbxObject3d_->wtf.position;
	attackHitBox.center = fbxObject3d_->wtf.position;
	state_->Update();
	fbxObject3d_->Update();

	DamageParticle->Update();
}

void Enemy::OnCollision(int damage) {
	hp->Damage(damage);
	
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 5.0f;
		Vector3 pos = fbxObject3d_->wtf.position;
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f + 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//速度
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		DamageParticle->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}

}

void Enemy::Draw() {
	if (hp->IsLive()) {
		fbxObject3d_->Draw();
	}
	EffDraw();
}

//状態を変更する
void Enemy::TransitionTo(EnemyState* state) {
	//削除
	delete state_;
	//新規作成
	state_ = state;
}
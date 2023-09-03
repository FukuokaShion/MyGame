#include "Enemy.h"
#include "FbxLoader.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyShooting.h"

Enemy::Enemy() {
	//���f������
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
	//�T�E���h
	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("fire.wav");
	audio->LoadWave("enemyat.wav");

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

void Enemy::Update(Vector3 playerPos) {
	if (hp->IsLive()) {
		//�����蔻��
		bodyHitBox.center = fbxObject3d_->wtf.position;
		attackHitBox.center = fbxObject3d_->wtf.position;

		//�s��
		state_->Update(playerPos);

		//�I�u�W�F�N�g
		fbxObject3d_->Update();

		//�e
		bullets.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
		for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
			bullet->Update();
		}
	}
	//�p�[�e�B�N��
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
}

void Enemy::ObjDraw() {
	for (std::unique_ptr<EnemyBullet>& bullet : bullets) {
		bullet->Draw();
	}
	particle->Draw();
}

void Enemy::CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(pos, velocity, liveLimit, stayTime);
	bullets.push_back(std::move(newBullet));
}

//��Ԃ�ύX����
void Enemy::TransitionTo(EnemyState* state) {
	//�폜
	delete state_;
	//�V�K�쐬
	state_ = state;
}

void Enemy::PlayWave(const std::string& filename) {
	if (filename == "fire.wav") {
		pSourceVoice[0] = audio->PlayWave("fire.wav");
	}else if (filename == "enemyat.wav") {
		pSourceVoice[1] = audio->PlayWave("enemyat.wav");
	}
}
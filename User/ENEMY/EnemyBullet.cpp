#include "EnemyBullet.h"

Model* EnemyBullet::model = nullptr;

EnemyBullet::EnemyBullet() {
}

EnemyBullet::~EnemyBullet() {
	delete obj;
}

void EnemyBullet::StaticInitialize() {
	model = Model::LoadFromOBJ("boll");
}
void EnemyBullet::StaticFinalize() {
	delete model;
}

void EnemyBullet::Initialize(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	obj = Object3d::Create();
	obj->SetModel(model);
	obj->wtf.position = pos;
	this->velocity_ = velocity;

	liveTimer = liveLimit;
	this->stayTime_ = stayTime;
	isDead = false;

	sphere = new Sphere;
	sphere->radius = 1.0f;
	sphere->center = pos;
	CollisionManager::GetInstance()->AddCollider(sphere);
}

void EnemyBullet::Update() {
	if (stayTime_ < 0) {
		liveTimer--;
		if (liveTimer < 0) {
			isDead = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere);
		}
		obj->wtf.position += velocity_;
	}
	else {
		stayTime_--;
	}

	if (sphere->isHit == true) {
		isDead = true;
		CollisionManager::GetInstance()->RemoveCollider(sphere);
	}
	sphere->center = obj->wtf.position;
	obj->Update();
}

void EnemyBullet::Draw() {
	obj->Draw();
}
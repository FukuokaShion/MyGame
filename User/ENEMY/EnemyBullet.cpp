/**
 * @file EnemyBullet.cpp
 * @brief 敵の弾
 */

#include "EnemyBullet.h"

Model* EnemyBullet::model_ = nullptr;

EnemyBullet::EnemyBullet() {
}

EnemyBullet::~EnemyBullet() {
	delete obj_;
}

void EnemyBullet::StaticInitialize() {
	model_ = Model::LoadFromOBJ("boll");
}
void EnemyBullet::StaticFinalize() {
	delete model_;
}

void EnemyBullet::Initialize(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime) {
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->wtf.position = pos;
	velocity_ = velocity;

	liveTimer_ = liveLimit;
	stayTime_ = stayTime;
	isDead_ = false;

	sphere_ = new BaseCollider;
	sphere_->SetRad(1.0f);
	sphere_->SetCenter(pos);
	sphere_->SetAttribute(Attribute::EnemyBullet);

	CollisionManager::GetInstance()->AddCollider(sphere_);
}

void EnemyBullet::Update() {
	if (stayTime_ < 0) {
		liveTimer_--;
		if (liveTimer_ < 0) {
			isDead_ = true;
			CollisionManager::GetInstance()->RemoveCollider(sphere_);
		}
		obj_->wtf.position += velocity_;
	}
	else {
		stayTime_--;
	}

	if (sphere_->GetIsHit().playerBody == true) {
		isDead_ = true;
		CollisionManager::GetInstance()->RemoveCollider(sphere_);
	}
	sphere_->SetCenter(obj_->wtf.position);
	obj_->Update();
}

void EnemyBullet::Draw() {
	//obj_->Draw();
}
/**
 * @file EnemyEarthquake.cpp
 * @brief 敵の地面攻撃
 */

#include"EnemyEarthquake.h"

//Model* Earthquake::model_ = nullptr;

Earthquake::Earthquake() {};
Earthquake::~Earthquake() {
	delete obj_;
	delete model_;
};

//void Earthquake::StaticInitialize() {
//	model_ = Model::LoadFromOBJ("cylinder");
//}
//
//void  Earthquake::StaticFinalize() {
//	delete model_;
//}

void Earthquake::Initialize(Vector3 createPos) {
	model_ = Model::LoadFromOBJ("cylinder");
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->wtf.position = createPos;
	obj_->wtf.scale = { 8,0.01f,8 };

	timer_ = 0;
	liveTime_ = 20;
	isDead_ = false;

	addSizeSpeed_ = 0.1f;
	maxSize_ = 1.0f;
}

void Earthquake::Update() {
	timer_++;
	obj_->Update();

	if (obj_->wtf.scale.y < maxSize_) {
		obj_->wtf.scale.y += addSizeSpeed_;
	}

	if (timer_ > liveTime_) {
		isDead_ = true;
	}
}

void Earthquake::Draw() {
	obj_->Draw();
}

bool Earthquake::attack() {
	if (timer_ > 10) {
		return true;
	}
	return false;
}
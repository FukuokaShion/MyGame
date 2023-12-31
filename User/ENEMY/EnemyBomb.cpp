/**
 * @file EnemyBomb.cpp
 * @brief 敵の爆弾
 */

#include "EnemyBomb.h"

Model* EnemyBomb::model_ = nullptr;

EnemyBomb::EnemyBomb() {
}

EnemyBomb::~EnemyBomb() {
	delete obj_;
}

void EnemyBomb::StaticInitialize() {
	model_ = Model::LoadFromOBJ("boll");
}

void EnemyBomb::StaticFinalize() {
	delete model_;
}

void EnemyBomb::Initialize(Vector3 creatPos) {
	startRad_ = 0.5f;
	obj_ = Object3d::Create();
	obj_->SetModel(model_);
	obj_->wtf.scale = { startRad_ ,startRad_ ,startRad_ };
	obj_->wtf.position = creatPos;

	stayTime_ = 80;
	timer_ = 0;
	isFired_ = false;
	velocity_ = { 0,0,0 };
	explosionTime_ = 80;
	isExplosion_ = false;
	isDead_ = false;
	sizeChangeRate_ = 0.3f;
	maxRad_ = 6.0f;
	speed_ = 1.6f;

	sphere_ = new BaseCollider;
	sphere_->SetRad(startRad_);
	sphere_->SetCenter(obj_->wtf.position);
	const int power = 200;
	sphere_->SetPower(power);
	sphere_->SetAttribute(Attribute::EnemyBullet);

	CollisionManager::GetInstance()->AddCollider(sphere_);
}

void EnemyBomb::Update(Vector3 stayPos,Vector3 playerPos) {
	timer_++;
	if (isFired_ == false) {
		obj_->wtf.position = stayPos;
		if (timer_ == stayTime_) {
			//時間経過で発射
			isFired_ = true;
			velocity_ = playerPos - obj_->wtf.position;
			velocity_.nomalize();
			velocity_ *= speed_;
		}
	}else if (isFired_ == true) {
		//地面に接触で移動停止
		if (obj_->wtf.position.y >= 0) {
			obj_->wtf.position += velocity_;
			timer_ = 0;
		}
		else {
			//時間経過で爆発
			if (timer_ > explosionTime_) {
				isExplosion_ = true;
			}
			//爆発で広がる
			if (isExplosion_) {
				obj_->wtf.scale += {sizeChangeRate_, sizeChangeRate_, sizeChangeRate_};
				sphere_->SetRad(obj_->wtf.scale.x);
			}
			//一定のサイズに到達で消滅
			if (sphere_->GetRad() > maxRad_) {
				isDead_ = true;
			}
		}
	}

	if (sphere_->GetIsHit().playerBody == true || isDead_ == true) {
		CollisionManager::GetInstance()->RemoveCollider(sphere_);
	}

	sphere_->SetCenter(obj_->wtf.position);
	obj_->Update();
}

void EnemyBomb::Draw() {
	obj_->Draw();
}
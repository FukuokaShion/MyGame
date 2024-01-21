/**
 * @file CollisionManager.cpp
 * @brief 当たり判定のチェック
 */

#include"CollisionManager.h"
#include"Collision.h"

void CollisionManager::Initialize() {
	model_ = Model::LoadFromOBJ("collider");
	for (int i = 0; i < maxCol_; i++) {
		objects_[i] = Object3d::Create();
		objects_[i]->SetModel(model_.get());
	}
	isPlayerHit_ = false;
	isEnemyHit_ = false;
}

CollisionManager::~CollisionManager() {
}

CollisionManager* CollisionManager::GetInstance(){
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::AddCollider(BaseCollider* collide){
	colliders_.push_front(collide);
};

void CollisionManager::RemoveCollider(BaseCollider* collide){
	colliders_.remove(collide);
};

void CollisionManager::Finalize() {
	colliders_.clear();
};

void CollisionManager::CheakCol() {
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	Vector3 hitPos;
	itA = colliders_.begin();
	for (; itA != colliders_.end(); ++itA) {
		BaseCollider* colA = *itA;
		itB = itA;
		++itB;

		for (; itB != colliders_.end(); ++itB) {
			BaseCollider* colB = *itB;
			//自機と敵突進
			if (colA->GetAttribute() == Attribute::PlyerBody && colB->GetAttribute() == Attribute::EnemyAttack) {
				if (isPlayerHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
						colA->IsHit(Attribute::EnemyAttack, hitPos);
						colA->SetDamage(colB->GetPower());
						colB->IsHit(Attribute::PlyerBody, hitPos);
						isPlayerHit_ = true;
					}
				}
			}else if (colB->GetAttribute() == Attribute::PlyerBody && colA->GetAttribute() == Attribute::EnemyAttack) {
				if (isPlayerHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colB, *colA, &hitPos)) {
						colB->IsHit(Attribute::EnemyAttack, hitPos);
						colB->SetDamage(colA->GetPower());
						colA->IsHit(Attribute::PlyerBody, hitPos);
						isPlayerHit_ = true;
					}
				}
			}
			//自機と敵弾
			else if (colA->GetAttribute() == Attribute::PlyerBody && colB->GetAttribute() == Attribute::EnemyBullet) {
				if (isPlayerHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
						colA->IsHit(Attribute::EnemyBullet, hitPos);
						colA->SetDamage(colB->GetPower());
						colB->IsHit(Attribute::PlyerBody, hitPos);
						isPlayerHit_ = true;
					}
				}
			}else if (colB->GetAttribute() == Attribute::PlyerBody && colA->GetAttribute() == Attribute::EnemyBullet) {
				if (isPlayerHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colB, *colA, &hitPos)) {
						colB->IsHit(Attribute::EnemyBullet, hitPos);
						colB->SetDamage(colA->GetPower());
						colA->IsHit(Attribute::PlyerBody, hitPos);
						isPlayerHit_ = true;
					}
				}
			}
			//自機攻撃と敵機
			else if (colA->GetAttribute() == Attribute::PlayerAttack && colB->GetAttribute() == Attribute::EnemyBody) {
				if (isEnemyHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colB, *colA, &hitPos)) {
						colA->IsHit(Attribute::EnemyBody, hitPos);
						colB->SetDamage(colA->GetPower());
						colB->IsHit(Attribute::PlayerAttack , hitPos);
						isEnemyHit_ = true;
					}
				}
			}else if (colB->GetAttribute() == Attribute::PlayerAttack && colA->GetAttribute() == Attribute::EnemyBody) {
				if (isEnemyHit_ == false) {
					if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
						colB->IsHit(Attribute::EnemyBody, hitPos);
						colA->SetDamage(colB->GetPower());
						colA->IsHit(Attribute::PlayerAttack, hitPos);
						isEnemyHit_ = true;
					}
				}
			}
		}
	}
}


void CollisionManager::GetPlayerAttack(bool playerIsAttack) {
	if (playerIsAttack == false) {
		isEnemyHit_ = false;
	}
}

void CollisionManager::GetEnemyAttack(bool enemyIsAttack) {
	if (enemyIsAttack == false) {
		isPlayerHit_ = false;
	}
}


void CollisionManager::DrawCollider() {
	std::forward_list<BaseCollider*>::iterator it;
	it = colliders_.begin();
	int i = 0;

	for (; it != colliders_.end(); ++it) {
		BaseCollider* col = *it;
		objects_[i]->wtf.position = col->GetCenter();
		objects_[i]->wtf.scale = { col->GetRad(),col->GetRad() ,col->GetRad() };
		objects_[i]->Update();
		objects_[i]->Draw();
		i++;
	}
}
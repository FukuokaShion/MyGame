#include"CollisionManager.h"
#include"Collision.h"

CollisionManager* CollisionManager::GetInstance(){
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheakCol() {
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;
	Vector3 hitPos;
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA) {
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB) {
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;
			//自機と敵突進
			if (colA->GetAttribute() == Attribute::PlyerBody && colB->GetAttribute() == Attribute::EnemyAttack) {
				if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
					colA->IsHit(Attribute::EnemyAttack, hitPos);
					colB->IsHit(Attribute::PlyerBody, hitPos);
				}
			}else if(colB->GetAttribute() == Attribute::PlyerBody && colA->GetAttribute() == Attribute::EnemyAttack) {
				if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
					colB->IsHit(Attribute::EnemyAttack, hitPos);
					colA->IsHit(Attribute::PlyerBody, hitPos);
				}
			}
			//自機と敵弾
			else if (colA->GetAttribute() == Attribute::PlyerBody && colB->GetAttribute() == Attribute::EnemyBullet) {
				if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
					colA->IsHit(Attribute::EnemyBullet, hitPos);
					colB->IsHit(Attribute::PlyerBody, hitPos);
				}
			}else if (colB->GetAttribute() == Attribute::PlyerBody && colA->GetAttribute() == Attribute::EnemyBullet) {
				if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
					colB->IsHit(Attribute::EnemyBullet, hitPos);
					colA->IsHit(Attribute::PlyerBody, hitPos);
				}
			}
			//自機攻撃と敵機
			else if (colA->GetAttribute() == Attribute::PlayerAttack && colB->GetAttribute() == Attribute::EnemyBody) {
				if (isEnemyHit == false) {
					if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
						colA->IsHit(Attribute::EnemyBody, hitPos);
						colB->IsHit(Attribute::PlayerAttack , hitPos);
					}
				}
			}else if (colB->GetAttribute() == Attribute::PlayerAttack && colA->GetAttribute() == Attribute::EnemyBody) {
				if (isEnemyHit == false) {
					if (Collision::CheckSphere2Sphere(*colA, *colB, &hitPos)) {
						colB->IsHit(Attribute::EnemyBody, hitPos);
						colA->IsHit(Attribute::PlayerAttack, hitPos);
					}
				}
			}
		}
	}
}
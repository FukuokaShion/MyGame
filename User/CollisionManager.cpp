#include"CollisionManager.h"
#include"Collision.h"

#include"Player.h"
#include"Enemy.h"

Player* CollisionManager::player_ = nullptr;
Enemy* CollisionManager::enemy_ = nullptr;

bool CollisionManager::isPlayerHit;
bool CollisionManager::isEnemyHit;

void CollisionManager::CheckCollision() {
	//敵の攻撃
	Cylinder playerBody = player_->GetBodyHitBox();
	Sphere enemyAttack = enemy_->GetAttackHitBox();
	if (Collision::CheckSphere2Cylinder(enemyAttack, playerBody)) {
		//敵の攻撃
		if (enemy_->GetIsAttack()) {
			if (isPlayerHit == false) {
				player_->OnCollision(enemy_->GetPower());
				isPlayerHit = true;
			}
		}
		else {
			isPlayerHit = false;
		}
	}

	//プレイヤーの攻撃
	Vector3 hitPos;
	Sphere playerAttack = player_->GetAttackHitBox();
	Cylinder enemyBody = enemy_->GetBodyHitBox();
	if (Collision::CheckSphere2Cylinder(playerAttack, enemyBody, &hitPos)) {
		//プレイヤーの攻撃
		if (player_->GetIsAttack()) {
			if (isEnemyHit == false) {
				enemy_->OnCollision(player_->GetPower(), hitPos);
				isEnemyHit = true;
			}
		}
		else {
			isEnemyHit = false;
		}
	}
}

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheakCol() {
	std::forward_list<Sphere*>::iterator itA;
	std::forward_list<Sphere*>::iterator itB;
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA) {
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB) {
			Sphere* colA = *itA;
			Sphere* colB = *itB;
			//自機と敵突進
			if (colA->attribute == Attribute::PlyerBody && colB->attribute == Attribute::EnemyAttack) {
				if (Collision::CheckSphere2Sphere(*colA, *colB)) {
					colA->isHit.enemyAttack = true;
					colB->isHit.playerBody = true;
				}
			}
			//自機と敵弾
			if (colA->attribute == Attribute::PlyerBody && colB->attribute == Attribute::EnemyBullet) {
				if (Collision::CheckSphere2Sphere(*colA, *colB)) {
					colA->isHit.enemyBullet = true;
					colB->isHit.playerBody = true;
				}
			}
			//自機攻撃と敵機
			if (colA->attribute == Attribute::PlayerAttack && colB->attribute == Attribute::EnemyBody) {
				if (Collision::CheckSphere2Sphere(*colA, *colB)) {
					colA->isHit.enemyBody = true;
					colB->isHit.playerAttack = true;
				}
			}
		}
	}
}

Vector3 CollisionManager::Body2Body() {
	Vector3 velocity = { 0,0,0 };
	Cylinder playerBody = player_->GetBodyHitBox();
	Cylinder enemyBody = enemy_->GetBodyHitBox();

	if (Collision::CheckCylinder2Cylinder(enemyBody, playerBody)) {
		//押し出し処理
		//一方的にプレイヤーが押される
		Vector3 distance = playerBody.center - enemyBody.center;
		velocity = distance;

		velocity.nomalize();
		velocity *= playerBody.radius + enemyBody.radius;

		velocity -= distance;
	}
	return velocity;
}
#include"CollisionManager.h"
#include"Collision.h"

#include"Player.h"
#include"Enemy.h"

Player* CollisionManager::player_ = nullptr;
Enemy* CollisionManager::enemy_ = nullptr;

bool CollisionManager::isPlayerHit;
bool CollisionManager::isEnemyHit;

void CollisionManager::CheckCollision() {
	//�G�̍U��
	Cylinder playerBody = player_->GetBodyHitBox();
	if (Collision::CheckSphere2Cylinder(enemy_->attackHitBox, playerBody)) {
		//�G�̍U��
		if (enemy_->GetIsAttack()) {
			if (isPlayerHit == false) {
				player_->OnCollision(enemy_->GetPower());
				isPlayerHit = true;
			}
		}else {
			isPlayerHit = false;
		}
	}

	//�v���C���[�̍U��
	Vector3 hitPos;
	Sphere playerAttack = player_->GetAttackHitBox();
	if (Collision::CheckSphere2Cylinder(playerAttack, enemy_->bodyHitBox, &hitPos)) {
		//�v���C���[�̍U��
		if (player_->GetIsAttack()) {
			if (isEnemyHit == false) {
				enemy_->OnCollision(player_->GetPower(), hitPos);
				isEnemyHit = true;
			}
		}else {
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
	//�G�e�Ǝ��@
	Cylinder playerBody = player_->GetBodyHitBox();

	std::forward_list<Sphere*>::iterator itA;
	
	itA = colliders.begin();

	for (; itA != colliders.end(); ++itA) {
		Sphere* colA = *itA;

		if (Collision::CheckSphere2Cylinder(*colA, playerBody)) {
			//�G�̍U��
			player_->OnCollision(10);
			colA->isHit = true;
		}
	}
}

Vector3 CollisionManager::Body2Body() {
	Vector3 velocity = { 0,0,0 };
	Cylinder playerBody = player_->GetBodyHitBox();
	if (Collision::CheckCylinder2Cylinder(enemy_->bodyHitBox, playerBody)) {
		//�����o������
		//����I�Ƀv���C���[���������
		Vector3 distance = playerBody.center - enemy_->bodyHitBox.center;
		velocity = distance;

		velocity.nomalize();
		velocity *= playerBody.radius + enemy_->bodyHitBox.radius;

		velocity -= distance;
	}
	return velocity;
}
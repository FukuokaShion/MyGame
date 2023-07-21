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
	if (Collision::CheckSphere2Cylinder(enemy_->attackHitBox, player_->bodyHitBox)) {
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
	if (Collision::CheckSphere2Cylinder(player_->attackHitBox, enemy_->bodyHitBox)) {
		//�v���C���[�̍U��
		if (player_->GetIsAttack()) {
			if (isEnemyHit == false) {
				enemy_->OnCollision(player_->GetPower());
				isEnemyHit = true;
			}
		}else {
			isEnemyHit = false;
		}
	}
}

Vector3 CollisionManager::Body2Body() {
	Vector3 velocity = { 0,0,0 };
	if (Collision::CheckCylinder2Cylinder(enemy_->bodyHitBox, player_->bodyHitBox)) {
		//�����o������
		//����I�Ƀv���C���[���������
		Vector3 distance = player_->bodyHitBox.center - enemy_->bodyHitBox.center;
		velocity = distance;

		velocity.nomalize();
		velocity *= player_->bodyHitBox.radius + enemy_->bodyHitBox.radius;

		velocity -= distance;
	}
	return velocity;
}
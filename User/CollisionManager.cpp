#include"CollisionManager.h"
#include"Collision.h"

void CollisionManager::CheckCollision() {

	//�G�̍U��
	if (Collision::CheckSphere2Cylinder(enemy->attackHitBox, player->bodyHitBox)) {
		//�G�̍U��
		if (enemy->GetIsAttack()) {
			if (isPlayerHit == false) {
				player->OnCollision(enemy->GetPower());
				isPlayerHit = true;
			}
		}
		else {
			isPlayerHit = false;
		}
	}

	//�v���C���[�̍U��
	if (Collision::CheckSphere2Cylinder(player->attackHitBox, enemy->bodyHitBox)) {
		//�v���C���[�̍U��
		if (player->GetIsAttack()) {
			if (isEnemyHit == false) {
				enemy->OnCollision(player->GetPower());
				isEnemyHit = true;
			}
		}
		else {
			isEnemyHit = false;
		}
	}
}
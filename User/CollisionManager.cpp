#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	//�G�̍U��
	if (enemy->GetIsAttack()) {
		if (isPlayerHit == false) {
			player->OnCollision(enemy->GetPower());
			isPlayerHit = true;
		}
	}else {
		isPlayerHit = false;
	}

	//�v���C���[�̍U��
	//if (isEnemyHit == false) {
	//	//����10�_���[�W
	//	enemy->OnCollision(10);
	//}
}
#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	////���ɍ��W�̌v�Z(�����蔻��)�͂Ƃ��ĂȂ�

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
	if (player->GetIsAttack()) {
		if (isEnemyHit == false) {
			enemy->OnCollision(player->GetPower());
			isEnemyHit = true;
		}
	}else {
		isEnemyHit = false;
	}
}
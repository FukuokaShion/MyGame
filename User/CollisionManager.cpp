#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	if (enemy->GetIsAttack()) {
		if (playerIsHit == false) {
			player->OnCollision(enemy->GetPower());
			playerIsHit = true;
		}
	}else {
		playerIsHit = false;
	}

}
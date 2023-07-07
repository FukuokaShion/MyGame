#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	//“G‚ÌUŒ‚
	if (enemy->GetIsAttack()) {
		if (isPlayerHit == false) {
			player->OnCollision(enemy->GetPower());
			isPlayerHit = true;
		}
	}else {
		isPlayerHit = false;
	}

	//ƒvƒŒƒCƒ„[‚ÌUŒ‚
	//if (isEnemyHit == false) {
	//	//‰¼‚Å10ƒ_ƒ[ƒW
	//	enemy->OnCollision(10);
	//}
}
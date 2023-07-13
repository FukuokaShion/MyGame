#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	////‹¤‚ÉÀ•W‚ÌŒvŽZ(“–‚½‚è”»’è)‚Í‚Æ‚Á‚Ä‚È‚¢

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
	if (player->GetIsAttack()) {
		if (isEnemyHit == false) {
			enemy->OnCollision(player->GetPower());
			isEnemyHit = true;
		}
	}else {
		isEnemyHit = false;
	}
}
#include"CollisionManager.h"
#include"Collision.h"

void CollisionManager::CheckCollision() {

	//“G‚ÌUŒ‚
	if (Collision::CheckSphere2Cylinder(enemy->attackHitBox, player->bodyHitBox)) {
		//“G‚ÌUŒ‚
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

	//ƒvƒŒƒCƒ„[‚ÌUŒ‚
	if (Collision::CheckSphere2Cylinder(player->attackHitBox, enemy->bodyHitBox)) {
		//ƒvƒŒƒCƒ„[‚ÌUŒ‚
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
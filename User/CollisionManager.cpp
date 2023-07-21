#include"CollisionManager.h"
#include"Collision.h"

void CollisionManager::CheckCollision() {
	//‘Ì“¯Žm
	if (Collision::CheckCylinder2Cylinder(enemy->bodyHitBox, player->bodyHitBox)) {
		//‰Ÿ‚µo‚µˆ—
		//ˆê•û“I‚ÉƒvƒŒƒCƒ„[‚ª‰Ÿ‚³‚ê‚é
		Vector3 distance = player->bodyHitBox.center - enemy->bodyHitBox.center;
		Vector3 velocity = distance;

		velocity.nomalize();
		velocity *= player->bodyHitBox.radius + enemy->bodyHitBox.radius;

		velocity -= distance;

		player->Move(velocity);
	}

	//“G‚ÌUŒ‚
	if (Collision::CheckSphere2Cylinder(enemy->attackHitBox, player->bodyHitBox)) {
		//“G‚ÌUŒ‚
		if (enemy->GetIsAttack()) {
			if (isPlayerHit == false) {
				player->OnCollision(enemy->GetPower());
				isPlayerHit = true;
			}
		}else {
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
		}else {
			isEnemyHit = false;
		}
	}
}
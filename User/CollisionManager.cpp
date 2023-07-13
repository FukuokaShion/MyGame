#include"CollisionManager.h"

void CollisionManager::CheckCollision() {
	////共に座標の計算(当たり判定)はとってない

	//敵の攻撃
	if (enemy->GetIsAttack()) {
		if (isPlayerHit == false) {
			player->OnCollision(enemy->GetPower());
			isPlayerHit = true;
		}
	}else {
		isPlayerHit = false;
	}

	//プレイヤーの攻撃
	if (player->GetIsAttack()) {
		if (isEnemyHit == false) {
			enemy->OnCollision(player->GetPower());
			isEnemyHit = true;
		}
	}else {
		isEnemyHit = false;
	}
}
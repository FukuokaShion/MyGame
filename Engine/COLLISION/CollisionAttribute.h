#pragma once

//‘®«
enum class Attribute {
	PlyerBody,
	PlayerAttack,
	EnemyBody,
	EnemyAttack,
	EnemyBullet
};

//Õ“Ë‘ÎÛ
struct HitTarget {
	bool playerBody = false;
	bool playerAttack = false;
	bool enemyBody = false;
	bool enemyAttack = false;
	bool enemyBullet = false;
};
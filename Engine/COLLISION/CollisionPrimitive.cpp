/**
 * @file CollisionPrimitive.cpp
 * @brief 当たり判定の形状
 */

#include "CollisionPrimitive.h"

using namespace DirectX;

void BaseCollider::IsHit(Attribute attribute, Vector3 hitPos) {
	if (attribute == Attribute::PlayerAttack) {
		isHit_.playerAttack = true;
		hitPos_.playerAttack = hitPos;
	}else if (attribute == Attribute::PlyerBody) {
		isHit_.playerBody = true;
		hitPos_.playerBody = hitPos;
	}else if (attribute == Attribute::EnemyAttack) {
		isHit_.enemyAttack = true;
		hitPos_.enemyAttack = hitPos;
	}else if (attribute == Attribute::EnemyBody) {
		isHit_.enemyBody = true;
		hitPos_.enemyBody = hitPos;
	}else if (attribute == Attribute::EnemyBullet) {
		isHit_.enemyBullet = true;
		hitPos_.enemyBullet = hitPos;
	}
}


void BaseCollider::RemoveHit(Attribute attribute) {
	if (attribute == Attribute::PlayerAttack) {
		isHit_.playerAttack = false;
	}
	else if (attribute == Attribute::PlyerBody) {
		isHit_.playerBody = false;
	}
	else if (attribute == Attribute::EnemyAttack) {
		isHit_.enemyAttack = false;
	}
	else if (attribute == Attribute::EnemyBody) {
		isHit_.enemyBody = false;
	}
	else if (attribute == Attribute::EnemyBullet) {
		isHit_.enemyBullet = false;
	}
}

void Triangle::ComputeNormal()
{

	Vector3 p0_p1 = p1 - p0;
	Vector3 p0_p2 = p2 - p0;

	normal = p0_p1.cross(p0_p2);
	normal = normal.nomalize();

}
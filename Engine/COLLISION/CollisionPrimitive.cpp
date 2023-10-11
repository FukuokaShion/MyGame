#include "CollisionPrimitive.h"

using namespace DirectX;

void BaseCollider::IsHit(Attribute attribute, Vector3 hitPos) {
	if (attribute == Attribute::PlayerAttack) {
		isHit_.playerAttack;
		hitPos_.playerAttack = hitPos;
	}else if (attribute == Attribute::PlyerBody) {
		isHit_.playerBody;
		hitPos_.playerBody = hitPos;
	}else if (attribute == Attribute::EnemyAttack) {
		isHit_.enemyAttack;
		hitPos_.enemyAttack = hitPos;
	}else if (attribute == Attribute::EnemyBody) {
		isHit_.enemyBody;
		hitPos_.enemyBody = hitPos;
	}else if (attribute == Attribute::EnemyBullet) {
		isHit_.enemyBullet;
		hitPos_.enemyBullet = hitPos;
	}
}

void Triangle::ComputeNormal()
{

	Vector3 p0_p1 = p1 - p0;
	Vector3 p0_p2 = p2 - p0;

	normal = p0_p1.cross(p0_p2);
	normal = normal.nomalize();

}
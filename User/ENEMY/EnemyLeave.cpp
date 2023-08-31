#include"Enemy.h"
#include"EnemyLeave.h"
#include"EnemyStandby.h"

void Leave::Update() {
	timer++;

	speed = distance / static_cast<float>(limit);
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(speed, enemyMat);

	//���W�ɑ���
	enemy_->Move(velocity);

	if (timer > limit) {
		//�ҋ@��Ԃɖ߂�
		enemy_->TransitionTo(new Standby);
	}
}
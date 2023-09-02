#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyStandby.h"

Approach::Approach() {
	limit = 180;
	timer = limit;
}

void Approach::Update(Vector3 playerPos) {
	timer--;
	//�v���C���[�̕�������
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	//���x�ݒ�
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//�����Ă�������ɍ��킹��
	Matrix4 enemyMat = enemy_->GetWtf().matWorld;
	velocity = Matrix4::bVelocity(velocity, enemyMat);

	//���W�ɑ���
	enemy_->Move(velocity);

	if (Vector3::Distance(enemy_->GetWtf().position, playerPos) < distance) {
		//��苗���ɂȂ�����ҋ@��ԂɈڍs
		enemy_->TransitionTo(new Standby);
	}
	if (timer < 0) {
		enemy_->TransitionTo(new Standby);
	}
}
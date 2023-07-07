#include"Action.h"
#include"Approach.h"
#include"Standby.h"

Approach::Approach() {
}

void Approach::Update() {
	//�v���C���[�̕�������
	float angle;
	angle = Vector3::Angle(playerWtf->position, EnemyWtf->position);
	EnemyWtf->rotation.y = angle;

	//���x�ݒ�
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//�����Ă�������ɍ��킹��
	velocity = Matrix4::bVelocity(velocity, EnemyWtf->matWorld);
	
	//���W�ɑ���
	EnemyWtf->position += velocity;

	if (Vector3::Distance(EnemyWtf->position, playerWtf->position) < distance) {
		//��苗���ɂȂ�����ҋ@��ԂɈڍs
		action_->TransitionTo(new Standby);
	}
}
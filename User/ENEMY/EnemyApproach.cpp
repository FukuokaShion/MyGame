#include"Enemy.h"
#include"EnemyApproach.h"
#include"EnemyStandby.h"

Approach::Approach() {
	limit = 180;
	timer = limit;
}

void Approach::Update() {
	timer--;
	//�v���C���[�̕�������
	Vector3 angle;
	angle.y = Vector3::Angle(enemy_->playerWtf->position, enemy_->fbxObject3d_->wtf.position);
	enemy_->fbxObject3d_->wtf.rotation = angle;

	//���x�ݒ�
	Vector3 velocity = { 0,0,0 };
	velocity += {0, 0, -speed};

	//�����Ă�������ɍ��킹��
	velocity = Matrix4::bVelocity(velocity, enemy_->fbxObject3d_->wtf.matWorld);

	//���W�ɑ���
	enemy_->fbxObject3d_->wtf.position += velocity;

	if (Vector3::Distance(enemy_->fbxObject3d_->wtf.position, enemy_->playerWtf->position) < distance) {
		//��苗���ɂȂ�����ҋ@��ԂɈڍs
		enemy_->TransitionTo(new Standby);
	}
	if (timer < 0) {
		enemy_->TransitionTo(new Standby);
	}
}
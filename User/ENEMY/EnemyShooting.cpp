#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->AnimationChange(0);
	interval = 25;
	ShotTimer = interval;
	shotMax = 3;
	shotNum = 0;
	bulletLiveLimit = 60;
	speed = 2;
}

void EnemyShooting::Update(Vector3 playerPos) {
	//�v���C���[�̕�������
	float angle;
	angle = Vector3::Angle(playerPos, enemy_->GetWtf().position);
	enemy_->RotaY(angle);

	ShotTimer--;
	if (ShotTimer < 0) {
		
		//���x�ݒ�
		Vector3 velocity = { 0,0,0 };
		velocity += {0, 0, -speed};

		//�����Ă�������ɍ��킹��
		Matrix4 enemyMat = enemy_->GetWtf().matWorld;
		velocity = Matrix4::bVelocity(velocity, enemyMat);

		//�e����
		enemy_->CreatBullet(enemy_->GetWtf().position, velocity, bulletLiveLimit);
		
		//���̔��˂܂ł̎���
		ShotTimer = interval;

		//���ː�
		shotNum++;
	}
	
	//��Ԉڍs
	if (shotNum >= shotMax) {
		enemy_->TransitionTo(new Standby);
	}
}
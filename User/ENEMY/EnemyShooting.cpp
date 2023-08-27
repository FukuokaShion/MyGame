#include"EnemyShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyShooting::EnemyShooting() {
	enemy_->fbxObject3d_->PlayAnimation(0);
	interval = 25;
	ShotTimer = interval;
	shotMax = 3;
	shotNum = 0;
	bulletLiveLimit = 60;
	speed = 2;
}

void EnemyShooting::Update() {
	//�v���C���[�̕�������
	Vector3 angle;
	angle.y = Vector3::Angle(enemy_->playerWtf->position, enemy_->fbxObject3d_->wtf.position);
	enemy_->fbxObject3d_->wtf.rotation = angle;
	
	ShotTimer--;
	if (ShotTimer < 0) {
		
		//���x�ݒ�
		Vector3 velocity = { 0,0,0 };
		velocity += {0, 0, -speed};

		//�����Ă�������ɍ��킹��
		velocity = Matrix4::bVelocity(velocity, enemy_->fbxObject3d_->wtf.matWorld);

		//�e����
		enemy_->CreatBullet(enemy_->fbxObject3d_->wtf.position, velocity , bulletLiveLimit);
		
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
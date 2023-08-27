#include"EnemyRoundShooting.h"
#include"Enemy.h"
#include"EnemyStandby.h"

EnemyRoundShooting::EnemyRoundShooting() {
	enemy_->fbxObject3d_->PlayAnimation(0);
	interval = 25;
	ShotTimer = interval;
	shotMax = 5;
	shotNum = 0;
	bulletLiveLimit = 60;
	speed = 2;
}

void EnemyRoundShooting::Update() {
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

		Vector3 creatPos;
		//�e����
		if (shotNum == 0) {
			creatPos = { 1.9f,2.6f,2 };
			creatPos = creatPos * enemy_->fbxObject3d_->wtf.matWorld;
			enemy_->CreatBullet(creatPos, velocity, bulletLiveLimit, interval * 4);
		}else if (shotNum == 1) {
			creatPos = { 1.17f,0.4f,2 };
			creatPos = creatPos * enemy_->fbxObject3d_->wtf.matWorld;
			enemy_->CreatBullet(creatPos, velocity, bulletLiveLimit, interval * 3);
		}else if (shotNum == 2) {
			creatPos = { -1.17f,0.4f,2 };
			creatPos = creatPos * enemy_->fbxObject3d_->wtf.matWorld;
			enemy_->CreatBullet(creatPos, velocity, bulletLiveLimit, interval * 2);
		}else if (shotNum == 3) {
			creatPos = { -1.9f,2.6f,2 };
			creatPos = creatPos * enemy_->fbxObject3d_->wtf.matWorld;
			enemy_->CreatBullet(creatPos, velocity, bulletLiveLimit, interval * 1);
		}else if (shotNum == 4) {
			creatPos = { 0,4,2 };
			creatPos = creatPos * enemy_->fbxObject3d_->wtf.matWorld;
			enemy_->CreatBullet(creatPos, velocity, bulletLiveLimit);
		}


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
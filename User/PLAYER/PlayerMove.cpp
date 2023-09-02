#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerMove::PlayerMove() {
	player_->AnimationChange(0);
	limit = 600;
	timer = 0;
	player_->PlayWav("run.wav");
}

void PlayerMove::Update() {
	Move();
	Rota();
	StateTransition();
}

void PlayerMove::Move() {
	timer++;
	if (timer > limit) {
		timer = 0;
		player_->StopWav();
		player_->PlayWav("run.wav");
	}

	//�ړ���
	Vector3 velocity = { 0,0,0 };
	//�ړ����x
	float speed = 0.5f;

	//�X�e�B�b�N���͕����擾
	Vector2 stickVec = input->GetLeftStickVec();
	//�ړ������ɕϊ�
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//�P�ʃx�N�g����
	velocity = velocity.nomalize();
	//�ړ��x�N�g���ɕϊ�
	velocity *= speed;

	//�J�����������Ă�������ɍ��킹��
	Transform direction = player_->GetCamWtf();
	direction.rotation.x = 0;
	direction.UpdateMat();
	velocity = Matrix4::bVelocity(velocity, direction.matWorld);
	player_->Move(velocity);
}

void PlayerMove::Rota() {
	if (input->LeftStickInput()) {
		Vector2 stickVec = input->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		Transform camWtf = player_->GetCamWtf();
		player_->RotaY(theta + camWtf.rotation.y);
	}
}

void PlayerMove::StateTransition() {
	//�ҋ@���
	if (input->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
		player_->StopWav();
	}

	//���
	if (input->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//�U��
	if (input->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
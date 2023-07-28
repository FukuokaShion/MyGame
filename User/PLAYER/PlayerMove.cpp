#include"Player.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"

PlayerMove::PlayerMove() {
	player_->fbxObject3d_->PlayAnimation(2);
}

void PlayerMove::Update() {
	Move();
	Rota();
	StateTransition();
}

void PlayerMove::Move() {
	//�ړ���
	Vector3 velocity = { 0,0,0 };
	//�ړ����x
	float speed = 0.5f;

	//�X�e�B�b�N���͕����擾
	Vector2 stickVec = player_->input_->GetLeftStickVec();
	//�ړ������ɕϊ�
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//�P�ʃx�N�g����
	velocity = velocity.nomalize();
	//�ړ��x�N�g���ɕϊ�
	velocity *= speed;

	//�J�����������Ă�������ɍ��킹��
	Transform direction;
	direction = player_->camera_->wtf;
	direction.rotation.x = 0;
	direction.UpdateMat();
	velocity = Matrix4::bVelocity(velocity, direction.matWorld);
	player_->fbxObject3d_->wtf.position += velocity;

}

void PlayerMove::Rota() {
	if (player_->input_->LeftStickInput()) {
		Vector2 stickVec = player_->input_->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));

		player_->fbxObject3d_->wtf.rotation.y = theta + player_->camera_->wtf.rotation.y;
	}
}

void PlayerMove::StateTransition() {
	if (player_->input_->LeftStickInput() == false) {
		player_->TransitionTo(new PlayerStandby);
	}

	//��
	if (player_->input_->PButtonTrigger(X)) {
		player_->hp->Heal(10);
	}

	//���
	if (player_->input_->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerAvoid);
	}

	//�U��
	if (player_->input_->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}
}
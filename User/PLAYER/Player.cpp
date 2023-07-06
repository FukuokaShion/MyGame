#include "Player.h"
#include "FbxLoader.h"

Player::Player() {
	//���f������
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	hp = new PlayerHp;
}

Player::~Player() {
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Initialize(Input* input) {
	input_ = input;
	hp->Initialize();

}

void Player::Update() {
	Move();
	Rota();
	CamRota();

	fbxObject3d_->Update();
}

void Player::Move() {
	//�ړ���
	Vector3 velocity = { 0.2f,0,0 };
	//�ړ����x
	float speed = 0.5f;

	//�X�e�B�b�N���͕����擾
	Vector2 stickVec = input_->GetLeftStickVec();
	//�ړ������ɕϊ�
	velocity.x = stickVec.x;
	velocity.z = stickVec.y;
	//�P�ʃx�N�g����
	velocity = velocity.nomalize();
	//�ړ��x�N�g���ɕϊ�
	velocity *= speed;

	//�J�����������Ă�������ɍ��킹��
	velocity = bVelocity(velocity,camera_->wtf);

	fbxObject3d_->wtf.position += velocity;
}

void Player::Rota() {
	if (input_->LeftStickInput()) {
		Vector2 stickVec = input_->GetLeftStickVec();

		float theta = static_cast<float>(atan2(stickVec.x, stickVec.y));
	
		fbxObject3d_->wtf.rotation.y = theta + camera_->wtf.rotation.y;
	}
}

void Player::CamRota() {
	//���E
	Vector3 theta;

	float PI = 3.1415f;
	Vector2 camRotaSpeed = { PI / 1800.0f, PI / 1800.0f };
	float sensitivity = 10.0f;

	if (input_->StickInput(R_LEFT)) {
		theta.y = camRotaSpeed.y * sensitivity;
	}
	else if (input_->StickInput(R_RIGHT)) {
		theta.y = -camRotaSpeed.y * sensitivity;
	}

	if (input_->StickInput(R_UP)) {
		theta.x = camRotaSpeed.x * sensitivity;
	}
	else if (input_->StickInput(R_DOWN)) {
		theta.x = -camRotaSpeed.x * sensitivity;
	}

	camera_->wtf.rotation += theta;
}

void Player::OnCollision(int damage) {
	hp->Damage(damage);
}

void Player::Draw() {
	fbxObject3d_->Draw();

}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//����
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	//result.y = velocity.x * worldTransform.matWorld.m[0][1] +
	//	velocity.y * worldTransform.matWorld.m[1][1] +
	//	velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}
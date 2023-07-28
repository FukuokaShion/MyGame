#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"

#include"PlayerHp.h"
#include"PlayerState.h"

class Player {
public:
	Player();
	~Player();
	void Initialize(Input* input);
	void SetCamera(Camera* camera) { camera_ = camera; };

	void Update();
	void OnCollision(int damage);
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void Draw();

	Transform* GetWtf() { return &fbxObject3d_->wtf; };
	bool IsLive() { return hp->IsLive(); };

	bool GetIsAttack() { return state_->GetIsAttack(); };
	int GetPower() { return state_->GetPower(); };

	void TransitionTo(PlayerState* state);

	void Move();
	void Rota();
	void CamRota();


public:
	//�J����
	Camera* camera_ = nullptr;

	//�̓����蔻��
	Cylinder bodyHitBox;

	//�U�������蔻��
	Sphere attackHitBox;

	//���f��
	FBXObject3d* fbxObject3d_ = nullptr;

	///�X�e�[�^�X
	PlayerHp* hp = nullptr;

	//����
	Input* input_ = nullptr;
private:
	//���f��
	FBXModel* fbxModel_ = nullptr;

	//�s��
	PlayerState* state_ = nullptr;

};
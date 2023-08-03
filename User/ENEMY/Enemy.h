#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"

#include"EnemyHp.h"
#include"EnemyState.h"

class Player;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();
	void SetPlayerTransform(Transform* playerWtf) { this->playerWtf = playerWtf; };

	void Update();
	void Draw();

	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; };
	void setPower(int power) { this->power = power; };

	void OnCollision(int damage,Vector3 hitPos);

	void TransitionTo(EnemyState* state);

	bool IsLive() { return hp->IsLive(); };

public:
	//�̓����蔻��
	Cylinder bodyHitBox;
	//�U�������蔻��
	Sphere attackHitBox;
	//�v���C���[���W
	Transform* playerWtf = nullptr;
	//�I�u�W�F�N�g
	FBXObject3d* fbxObject3d_ = nullptr;

private:
	//���f��
	FBXModel* fbxModel_ = nullptr;

	//�s��
	EnemyState* state_ = nullptr;
	//�X�e�[�^�X
	EnemyHp* hp = nullptr;

	//�U������
	bool isAttack;
	int power;

	EnemyParticle* particle = nullptr;
};
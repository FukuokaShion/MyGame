#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"

#include"EnemyHp.h"
#include"EnemyState.h"
#include"EnemyBullet.h"

class Player;

class Enemy {
public:
	//�ݒ�
	Enemy();
	~Enemy();
	void Initialize();

	//�X�V
	void Update(Vector3 playerPos);

	//�`��
	void Draw();
	void ObjDraw();

	//��Ԉȍ~
	void TransitionTo(EnemyState* state);

	//�A�j���[�V�����؂�ւ�
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	//���W
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };
	Transform GetWtf() { return fbxObject3d_->wtf; };

	//�U�������蔻��
	Sphere GetAttackHitBox() { return attackHitBox; };
	void SetAttackRad(float newRad) { attackHitBox.radius = newRad; };
	void SetAttackPos(Vector3 newPos) { attackHitBox.center = newPos; };

	//�̓����蔻��
	Cylinder GetBodyHitBox() { return bodyHitBox; };

	//��_������
	void OnCollision(int damage, Vector3 hitPos);

	//�X�e�[�^�X
	bool IsLive() { return hp->IsLive(); };
	int GetHp() { return hp->GetHp(); };
	bool GetIsAttack() { return isAttack; };
	int GetPower() { return power; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; };
	void setPower(int power) { this->power = power; };

	//�e����
	void CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

public:
	
	//��
	std::list<std::unique_ptr<EnemyBullet>> bullets;
private:
	//�s��
	EnemyState* state_ = nullptr;
	
	//�̗�
	EnemyHp* hp = nullptr;

	//�̓����蔻��
	Cylinder bodyHitBox;

	//�U�������蔻��
	Sphere attackHitBox;

	//���f��
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//�U������
	bool isAttack;
	int power;

	EnemyParticle* particle = nullptr;
};
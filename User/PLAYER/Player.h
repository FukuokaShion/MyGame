#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"Audio.h"

#include"PlayerHp.h"
#include"PlayerState.h"

class Player {
public:
	//�ݒ�
	Player();
	~Player();
	void Initialize(Input* input);
	void SetCamera(Camera* camera) { camera_ = camera; };

	//�X�V
	void Update();
	void CamRota();

	//�`��
	void Draw();

	//��Ԉڍs
	void TransitionTo(PlayerState* state);

	//�T�E���h
	void PlayWav(const std::string& filename);
	void StopWav();

	//FBX
	//�A�j���[�V�����؂�ւ�
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	//���W
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void SetPosY(float posY) { fbxObject3d_->wtf.position.y = posY; };
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };
	Transform GetWtf() { return fbxObject3d_->wtf; };
	Transform* GetWtfP() { return &fbxObject3d_->wtf; };
	Transform GetCamWtf() { return camera_->wtf; };

	//�U�������蔻��
	Sphere GetAttackHitBox() { return attackHitBox; };
	void SetAttackRad(float newRad) { attackHitBox.radius = newRad; };
	void SetAttackPos(Vector3 newPos) { attackHitBox.center = newPos; };

	//�̓����蔻��
	Cylinder GetBodyHitBox() { return bodyHitBox; };

	//��_������
	void OnCollision(int damage);
	
	//�X�e�[�^�X
	bool IsLive() { return hp->IsLive(); };
	int GetHp() { return hp->GetHp(); };
	int GetDamage() { return damageGauge; };
	bool GetIsAttack() { return state_->GetIsAttack(); };
	int GetPower() { return state_->GetPower(); };


private:
	//�J����
	Camera* camera_ = nullptr;
	//����
	Input* input_ = nullptr;
	//�T�E���h
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice[10] = {0};

	//�̗�
	PlayerHp* hp = nullptr;

	//�U�������蔻��
	Sphere attackHitBox;
	//�̓����蔻��
	Cylinder bodyHitBox;
	//HP�Q�[�W�Ǘ�
	int gaugeTimer;
	int gaugeLimit;
	int damageGauge;

	//���f��
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//�s��
	PlayerState* state_ = nullptr;
};
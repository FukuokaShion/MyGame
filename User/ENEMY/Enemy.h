#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"

#include"Action.h"
#include"EnemyHp.h"

class Player;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();
	void SetPlayerTransform(Transform* playerWtf);

	void Update();
	void Draw();

	bool GetIsAttack() { return action->GetIsAttack(); };
	int GetPower() { return action->GetPower(); };

	void OnCollision(int damage);
private:
	//���f��
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//�s��
	Action* action = nullptr;
	//�X�e�[�^�X
	EnemyHp* hp = nullptr;
};
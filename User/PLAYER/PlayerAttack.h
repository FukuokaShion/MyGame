#pragma once
#include"PlayerState.h"

//�U��
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();
	void Update() override;

private:
	void StateTransition() override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	Vector3 speed;
	Vector3 velocity;

	int timer;

	///�\������
	//����
	const int anticTime = 16;
	//�ړ�����
	const Vector3 anticDistance = { 0,0,2 };

	///�U��
	//����
	const int attackTime = 11;
	//�ړ�����
	const Vector3 attackDistance = { 0,0,1 };
	//�U����
	const int power_ = 10;

	///�㌄
	const int afterTime = 6;
};
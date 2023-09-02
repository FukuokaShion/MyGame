#pragma once
#include"EnemyState.h"

//�U��
class Attack : public EnemyState {
public:
	Attack();

	void Update(Vector3 playerPos) override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	///�\������
	//����
	const int anticTime = 20;
	//�ړ�����
	const Vector3 anticDistance = { 0,0,1 };

	///�U��
	//����
	const int attackTime = 15;
	//�ړ�����
	const Vector3 attackDistance = { 0,0,-3 };
	//�U����
	const int power = 10;

	///�㌄
	const int afterTime = 5;

};
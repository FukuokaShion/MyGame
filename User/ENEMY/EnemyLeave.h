#pragma once
#include"EnemyState.h"

//�ڋ�
class Leave : public EnemyState {
public:

	void Update() override;

private:
	//����
	const int limit = 10;
	//�ړ�����
	const Vector3 distance = { 0,0,7 };
};
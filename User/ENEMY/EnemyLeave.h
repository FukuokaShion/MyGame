#pragma once
#include"EnemyState.h"

//�ڋ�
class Leave : public EnemyState {
public:

	void Update(Vector3 playerPos) override;

private:
	//����
	const int limit = 10;
	//�ړ�����
	const Vector3 distance = { 0,0,7 };
};
#pragma once
#include"EnemyState.h"

//�ڋ�
class Approach : public EnemyState {
public:
	Approach();

	void Update() override;

private:
	//�ړ����x
	const float speed = 0.3f;
	//�ŏI�I�ȋ���
	const float distance = 4.0f;
	//
	int limit;
	int timer;
};
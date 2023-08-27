#pragma once
#include"EnemyState.h"

//�ˌ�
class EnemyShooting : public EnemyState {
public:
	EnemyShooting();

	void Update() override;

private:
	int interval;
	int ShotTimer;
	
	int shotMax;
	int shotNum;

	int bulletLiveLimit;
	float speed;
};
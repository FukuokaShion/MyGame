#pragma once
#include"EnemyState.h"

//�ҋ@
class EnemyStandby : public EnemyState {
public:
	EnemyStandby();

	void Update() override;

private:
	//�ҋ@����
	const int limit = 120;
	int timer = limit;

	//�ڋ߈ڍs����
	const float approachDistance = 4.0f;
};
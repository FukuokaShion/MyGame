#pragma once
#include"EnemyState.h"

//�ҋ@
class Standby : public EnemyState {
public:
	Standby();
	void Update() override;

private:
	//�ҋ@����
	const int limit = 120;

	//�ڋ߈ڍs����
	const float approachDistance = 4.0f;
};
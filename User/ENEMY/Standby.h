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
	int timer = limit;
};
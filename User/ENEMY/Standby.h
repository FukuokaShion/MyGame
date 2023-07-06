#pragma once
#include"EnemyState.h"

//待機
class Standby : public EnemyState {
public:
	Standby();

	void Update() override;

private:
	//待機時間
	const int limit = 120;
	int timer = limit;
};
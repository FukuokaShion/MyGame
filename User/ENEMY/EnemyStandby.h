#pragma once
#include"EnemyState.h"

//待機
class Standby : public EnemyState {
public:
	void Update() override;

private:
	//待機時間
	const int limit = 120;

	//接近移行距離
	const float approachDistance = 4.0f;
};
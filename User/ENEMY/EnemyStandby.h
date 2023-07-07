#pragma once
#include"EnemyState.h"

//‘Ò‹@
class EnemyStandby : public EnemyState {
public:
	EnemyStandby();

	void Update() override;

private:
	//‘Ò‹@ŠÔ
	const int limit = 120;
	int timer = limit;

	//Ú‹ßˆÚs‹——£
	const float approachDistance = 4.0f;
};
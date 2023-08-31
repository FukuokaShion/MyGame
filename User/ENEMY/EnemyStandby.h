#pragma once
#include"EnemyState.h"

//‘Ò‹@
class Standby : public EnemyState {
public:
	Standby();
	void Update(Vector3 playerPos) override;

private:
	//‘Ò‹@ŠÔ
	const int limit = 120;

	//Ú‹ßˆÚs‹——£
	const float approachDistance = 4.0f;
};
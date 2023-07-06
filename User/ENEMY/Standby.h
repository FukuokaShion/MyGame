#pragma once
#include"EnemyState.h"

//‘Ò‹@
class Standby : public EnemyState {
public:
	Standby();

	void Update() override;

private:
	//‘Ò‹@ŠÔ
	const int limit = 120;
	int timer = limit;
};
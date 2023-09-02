#pragma once
#include"EnemyState.h"

//Ú‹ß
class Leave : public EnemyState {
public:

	void Update(Vector3 playerPos) override;

private:
	//ŠÔ
	const int limit = 10;
	//ˆÚ“®‹——£
	const Vector3 distance = { 0,0,7 };
};
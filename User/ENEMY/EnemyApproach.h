#pragma once
#include"EnemyState.h"

//Ú‹ß
class Approach : public EnemyState {
public:
	Approach();

	void Update() override;

private:
	//ˆÚ“®‘¬“x
	const float speed = 0.3f;
	//ÅI“I‚È‹——£
	const float distance = 4.0f;
	//
	int limit;
	int timer;
};
#pragma once
#include"EnemyState.h"

//UŒ‚
class Attack : public EnemyState {
public:
	Attack();

	void Update(Vector3 playerPos) override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	///—\”õ“®ì
	//ŠÔ
	const int anticTime = 20;
	//ˆÚ“®‹——£
	const Vector3 anticDistance = { 0,0,1 };

	///UŒ‚
	//ŠÔ
	const int attackTime = 15;
	//ˆÚ“®‹——£
	const Vector3 attackDistance = { 0,0,-3 };
	//UŒ‚—Í
	const int power = 10;

	///ŒãŒ„
	const int afterTime = 5;

};
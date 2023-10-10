#pragma once
#include"PlayerState.h"

//攻撃
class PlayerAttack : public PlayerState {
public:
	PlayerAttack();
	void Update() override;

private:
	void StateTransition() override;

private:
	enum class Action {
		Antic,
		Attack,
		After,
	};
	Action action;

	Vector3 speed;
	Vector3 velocity;

	int timer;

	///予備動作
	//時間
	const int anticTime = 16;
	//移動距離
	const Vector3 anticDistance = { 0,0,1 };

	///攻撃
	//時間
	const int attackTime = 11;
	//移動距離
	const Vector3 attackDistance = { 0,0,1 };
	//攻撃力
	const int power_ = 10;

	///後隙
	const int afterTime = 6;
};
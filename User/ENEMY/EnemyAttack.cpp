#include"EnemyAction.h"
#include"EnemyAttack.h"
#include"EnemyStandby.h"

EnemyAttack::EnemyAttack() {
}

//UŒ‚
void EnemyAttack::Update() {
	timer--;
	if (timer > 15) {
		EnemyWtf->position += {0, 0.08f , 0};
	}else if(timer > 0) {
		EnemyWtf->position += {0, -0.13f, 0};
		isAttack = true;
		power = 10;
	}else {
		action_->TransitionTo(new EnemyStandby);
	}
}
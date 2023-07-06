#include"Action.h"
#include"Standby.h"
#include"EnemyAttack.h"
#include"Approach.h"

Standby::Standby() {
	timer = limit;
}

//待機
void Standby::Update(){
	timer--;
	//状態切り替え
	if (timer < 0) {
		if (EnemyWtf->position.z - playerWtf->position.z > 4.0f) {
			//遠いならApproachに移行
			action_->TransitionTo(new Approach);
		}else {
			//近いなら攻撃する
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
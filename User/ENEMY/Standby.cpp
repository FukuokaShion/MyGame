#include"Action.h"
#include"Standby.h"
#include"EnemyAttack.h"
#include"Approach.h"

Standby::Standby() {
	timer = limit;
}

//�ҋ@
void Standby::Update(){
	timer--;
	//��Ԑ؂�ւ�
	if (timer < 0) {
		if (EnemyWtf->position.z - playerWtf->position.z > 4.0f) {
			//�����Ȃ�Approach�Ɉڍs
			action_->TransitionTo(new Approach);
		}else {
			//�߂��Ȃ�U������
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
#include"EnemyAction.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"

EnemyStandby::EnemyStandby() {
	timer = limit;
}

//�ҋ@
void EnemyStandby::Update(){
	timer--;
	//��Ԑ؂�ւ�
	if (timer < 0) {
		if (Vector3::Distance(EnemyWtf->position, playerWtf->position) > approachDistance) {
			//�����Ȃ�Approach�Ɉڍs
			action_->TransitionTo(new Approach);
		}else {
			//�߂��Ȃ�U������
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
#include"EnemyAction.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"

EnemyStandby::EnemyStandby() {
	timer = limit;
}

//‘Ò‹@
void EnemyStandby::Update(){
	timer--;
	//ó‘ÔØ‚è‘Ö‚¦
	if (timer < 0) {
		if (Vector3::Distance(EnemyWtf->position, playerWtf->position) > approachDistance) {
			//‰“‚¢‚È‚çApproach‚ÉˆÚs
			action_->TransitionTo(new Approach);
		}else {
			//‹ß‚¢‚È‚çUŒ‚‚·‚é
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
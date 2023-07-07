#include"Action.h"
#include"Standby.h"
#include"EnemyAttack.h"
#include"Approach.h"

Standby::Standby() {
	timer = limit;
}

//‘Ò‹@
void Standby::Update(){
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
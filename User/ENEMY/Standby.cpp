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
		if (EnemyWtf->position.z - playerWtf->position.z > 4.0f) {
			//‰“‚¢‚È‚çApproach‚ÉˆÚs
			action_->TransitionTo(new Approach);
		}else {
			//‹ß‚¢‚È‚çUŒ‚‚·‚é
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
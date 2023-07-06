#include"Action.h"
#include"EnemyAttack.h"
#include"Standby.h"

EnemyAttack::EnemyAttack() {
}

//UŒ‚
void EnemyAttack::Update() {
	//‰¼‚Å‰¡‚ÉˆÚ“®‚·‚é
	EnemyWtf->position += {-0.1f, 0, 0 };
	//if (true) {
	//	action_->TransitionTo(new Standby);
	//}
}
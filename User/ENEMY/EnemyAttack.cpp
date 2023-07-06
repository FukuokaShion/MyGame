#include"Action.h"
#include"EnemyAttack.h"
#include"Standby.h"

void EnemyAttack::Update(Transform* wtf) {
	{
		wtf->position += {-0.1f, 0, 0 };
		//ó‘ÔØ‚è‘Ö‚¦
		if (wtf->position.x < -3) {
			action_->TransitionTo(new Standby);
		}
	}
}
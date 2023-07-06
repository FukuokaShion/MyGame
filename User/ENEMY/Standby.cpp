#include"Action.h"
#include"Standby.h"
#include"EnemyAttack.h"

void Standby::Update(Transform* wtf){
	{
		wtf->position += {0.1f, 0, 0};
		//ó‘ÔØ‚è‘Ö‚¦
		if (wtf->position.x > 3) {
			action_->TransitionTo(new EnemyAttack);
		}
	}
}
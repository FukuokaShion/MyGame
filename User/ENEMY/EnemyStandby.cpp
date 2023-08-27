#include"Enemy.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"
#include"EnemyLeave.h"
#include"EnemyShooting.h"

Standby::Standby() {
	enemy_->fbxObject3d_->PlayAnimation(1);
}

//‘Ò‹@
void Standby::Update(){
	timer++;
	//ó‘ÔØ‚è‘Ö‚¦
	if (timer > limit) {
		if (Vector3::Distance(enemy_->fbxObject3d_->wtf.position, enemy_->playerWtf->position) > approachDistance) {
			if (rand() % 100 + 1 < 50) {
				enemy_->TransitionTo(new Approach);
			}else {
				enemy_->TransitionTo(new EnemyShooting);
			}
		}else {
			if (rand() % 100 + 1 < 50) {
				enemy_->TransitionTo(new Attack);
			}else {
				enemy_->TransitionTo(new Leave);
			}
		}
	}
}
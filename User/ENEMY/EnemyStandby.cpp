#include"Enemy.h"
#include"EnemyStandby.h"
#include"EnemyAttack.h"
#include"EnemyApproach.h"
#include"EnemyLeave.h"

//�ҋ@
void Standby::Update(){
	timer++;
	////��Ԑ؂�ւ�
	//if (timer > limit) {
	//	if (Vector3::Distance(enemy_->fbxObject3d_->wtf.position, enemy_->playerWtf->position) > approachDistance) {
	//		//�����Ȃ�Approach�Ɉڍs
	//		enemy_->TransitionTo(new Approach);
	//	}else {
	//		if (rand() % 100 + 1 < 50) {
	//			enemy_->TransitionTo(new Attack);
	//		}else {
	//			enemy_->TransitionTo(new Leave);
	//		}
	//	}
	//}
}
#include"Action.h"
#include"EnemyAttack.h"
#include"Standby.h"

EnemyAttack::EnemyAttack() {
}

//�U��
void EnemyAttack::Update() {
	//���ŉ��Ɉړ�����
	EnemyWtf->position += {-0.1f, 0, 0 };
	//if (true) {
	//	action_->TransitionTo(new Standby);
	//}
}
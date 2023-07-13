#include"PlayerAction.h"
#include"PlayerStandby.h"
#include"PlayerAttack.h"

PlayerStandby::PlayerStandby() {
}

//待機
void PlayerStandby::Update() {
	//状態切り替え

	if (input_->PushKey(DIK_SPACE)) {
		//仮でスペースキーで攻撃に移行
		action_->TransitionTo(new PlayerAttack);
	}
}
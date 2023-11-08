/**
 * @file PlayerStandby.cpp
 * @brief プレイヤーの待機パターン
 *        各行動後この状態になる
 */

#include"Player.h"

#include"PlayerStandby.h"
#include"PlayerAttack.h"
#include"PlayerAvoid.h"
#include"PlayerMove.h"
#include"PlayerJump.h"

PlayerStandby::PlayerStandby() {
	player_->AnimationChange(Player::Animation::STAND);
}

//待機
void PlayerStandby::Update() {
	StateTransition();
}

void PlayerStandby::StateTransition() {
	//回避
	//if (input->PButtonTrigger(A)) {
	//	player_->TransitionTo(new PlayerAvoid);
	//}
	//ジャンプ
	if (Input::GetInstance()->PButtonTrigger(A)) {
		player_->TransitionTo(new PlayerJump);
	}

	//攻撃
	if (Input::GetInstance()->PButtonTrigger(B)) {
		player_->TransitionTo(new PlayerAttack);
	}

	//移動
	if (Input::GetInstance()->LeftStickInput()) {
		player_->TransitionTo(new PlayerMove);
	}
}
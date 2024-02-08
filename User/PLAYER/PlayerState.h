/**
 * @file PlayerState.h
 * @brief プレイヤーのステートパターン基底
 */

#pragma once
#include"Transform.h"
#include"Input.h"
#include"GlobalVariables.h"

class Player;

class PlayerState {
public:
	PlayerState();
	virtual ~PlayerState() {};

	/**
	 * @brief プレイヤー本体をセット
	*/
	void SetPlayer(Player* player) { player_ = player; };
	
	/**
	 * @brief プレイヤーが攻撃常態かチェック
	*/
	bool GetIsAttack() { return isAttack_; };
	int GetPower() { return power_; };

	/**
	 * @brief 更新
	*/
	virtual void Update() = 0;

protected:
	/**
	 * @brief 状態移行
	*/
	virtual void StateTransition() = 0;
	/**
	 * @brief 調整項目の適用
	*/
	virtual void ApplyGlobalVariables() = 0;

protected:
	static Player* player_;

	//攻撃判定
	bool isAttack_;
	int power_;
};

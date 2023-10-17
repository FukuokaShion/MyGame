/**
 * @file EnemyHp.h
 * @brief 敵の体力を管理する
 */

#pragma once

class EnemyHp {
public:
	EnemyHp();
	~EnemyHp();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 体力上限セッター
	*/
	void SetMaxHp(int maxHp) { this->MaxHp = maxHp; };

	/**
	 * @brief 現在の体力取得
	*/
	int GetHp() { return hp; };
	
	/**
	 * @brief 生存フラグ
	*/
	bool IsLive() { return isLive; };

	/**
	 * @brief ダメージを受ける
	*/
	void Damage(int damage);
	
	/**
	 * @brief 回復
	*/
	void Heal(int heal);

private:
	//最大HP
	int MaxHp;
	//現在のHP
	int hp;
	//生存フラグ
	bool isLive;
};
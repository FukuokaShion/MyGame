/**
 * PlayerHp.h
 * プレイヤーの体力管理
 */

#pragma once

class PlayerHp {
public:
	PlayerHp();
	~PlayerHp();

	void Initialize();
	void SetMaxHp(int maxHp) { this->MaxHp = maxHp; };

	int GetHp() { return hp; };
	int GetOldHp() { return oldHp; };
	bool IsLive() { return isLive; };

	void Damage(int damage);
	void Heal(int heal);

private:
	//最大HP
	int MaxHp;
	//現在のHP
	int hp;
	//ダメージを受ける前の体力
	int oldHp;

	//生存フラグ
	bool isLive;

};
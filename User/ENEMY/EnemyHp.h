#pragma once

class EnemyHp {
public:
	EnemyHp();
	~EnemyHp();

	void Initialize();
	void SetMaxHp(int maxHp) { this->MaxHp = maxHp; };

	int GetHp() { return hp; };
	bool IsLive() { return isLive; };

	void Damage(int damage);
	void Heal(int heal);

private:
	//�ő�HP
	int MaxHp;
	//���݂�HP
	int hp;
	//�����t���O
	bool isLive;
};
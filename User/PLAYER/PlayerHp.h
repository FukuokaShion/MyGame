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
	//�ő�HP
	int MaxHp;
	//���݂�HP
	int hp;
	//�_���[�W���󂯂�O�̗̑�
	int oldHp;
	
	//�����t���O
	bool isLive;

};
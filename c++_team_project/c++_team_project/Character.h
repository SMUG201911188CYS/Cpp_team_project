#pragma once
#ifndef __Character_h__

#define __CHARACTER_H__
#include <string>
class Character {
private:
	int hp;
	int shield;
	int attackDamage;
	int passive;
public:
	Character();
	Character(int hp, int shield, int ad);

	void Set_HP(int hp) { if (hp < 0) this->hp = 0; else this->hp = hp; }
	void Set_AttackDamage(int ad) { this->attackDamage = ad; }
	void Set_Shield(int shield) { this->shield = shield; }
	void Set_Passive(int passive) { this->passive = passive; }

	int Get_HP() { return this->hp; }
	int Get_Shield() { return this->shield; }
	int Get_AttackDamage() { return this->attackDamage; }
	int Get_Passive() { return this->passive; }

	int normal_attack(Character& Hit_Object);
	bool Skill_Attack(Character& Hit_Object);
};


class Player : Character {
private :
	std::string arms; // ÆÈ
	std::string skill_discription; // ÆÈ ½ºÅ³ ¼³¸í
	int arms_skill_count;
	enum Arms {
		NONE = 0,
		Dori_Bear_arms = 15,
		Wings = 16,
		Twigs = 17,
		CatArms = 18,
		BarbieArms = 19,
		ICArms = 20,
		Wings_end = 412,
		Cat_end = 414,
	};
public :
	Player();

	bool Set_Arms(int arms);

	std::string Get_Arms() { return arms; }
	std::string Get_Skill_Discription() { return skill_discription; }
	int Get_Skill_Count() { return arms_skill_count; }

	int Skill_Attack(Character& Hit_Object);
};

class Boss : Character {
private:
	std::string boss_skill_list[4];
	int last_bossattack;
public:
	Boss();
	int Skill_Attack(Character& Hit_Object);
	std::string Get_Last_Attack_Name();
};


#endif // !__Character_h__


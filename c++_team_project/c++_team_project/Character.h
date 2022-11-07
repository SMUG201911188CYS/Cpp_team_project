#pragma once
#ifndef __Character_h__

#define __CHARACTER_H__

class Character {
private:
	int HP;
	int AttackDamage;
public:
	Character();
	Character(int hp, int ad);
	void Set_HP(int hp);
	void Set_AttackDamage(int ad);
};


class Player : Character {
private :
	int arms;
	int arms_skill_count;
	int passive;
public :
};

class Boss : Character {
private:

public:

};


#endif // !__Character_h__


#include "Character.h"
#include <iostream>

Character::Character() {
	this->HP = 0;
	this->AttackDamage = 0;
}

Character::Character(int hp, int ad) {
	this->HP = hp;
	this->AttackDamage = ad;
}
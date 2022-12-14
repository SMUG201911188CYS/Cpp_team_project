#include "enum.h"

Character::Character() {
	this->hp = 0;
	this->shield = 0;
	this->attackDamage = 0;
	this->passive = 0;
}

Character::Character(int hp, int shield, int ad) {
	this->hp = hp;
	this->shield = shield;
	this->attackDamage = ad;
	this->passive = 0;
}


// 도리베어(플레이어) 구현

Player::Player(int hp, int shield, int ad) : Character(hp, shield, ad) {
	this->arms = "없음";
	this->skill_discription = "없음";
	this->arms_skill_count = 0;
}

int Player::normal_attack(Character & Hit_Object) {
	int damage = this->Get_AttackDamage();
	Hit_Object.Set_HP(Hit_Object.Get_HP() - damage);
	return damage;
}

bool Player::Set_Arms(int arms) {
	if (arms == Dori_Bear_arms) {
		this->arms = "Dori_Bear_arms";
		this->skill_discription = "특수 공격이 없습니다.";
		this->arms_skill_count = 0;
		Set_AttackDamage(15);
	}
	else if (arms == Wings) {
		this->arms = "Wings";
		this->skill_discription = "회오리로 적을 가둡니다.";
		this->arms_skill_count = 3;
		Set_AttackDamage(20);
	}
	else if (arms == Twigs) {
		this->arms = "Twigs";
		this->skill_discription = "특수 공격이 없습니다.";
		this->arms_skill_count = 0;
		Set_AttackDamage(10);
	}
	else if (arms == CatArms) {
		this->arms = "CatArms";
		this->skill_discription = "냥냥펀치를 사용합니다.";
		this->arms_skill_count = 3;
		Set_AttackDamage(20);
	}
	else if (arms == BarbieArms) {
		this->arms = "BarbieArms";
		this->skill_discription = "특수 공격이 없습니다.";
		this->arms_skill_count = 0;
		Set_AttackDamage(15);
	}
	else if (arms == ICArms) {
		this->arms = "ICArms";
		this->skill_discription = "팔을 먹어 피를 회복합니다.";
		this->arms_skill_count = 2;
		Set_AttackDamage(10);
	}
	else {
		return false;
	}

	return true;
}

int Player::Skill_Attack(Character& Hit_Object, bool temp) {

	if (this->arms == "Wings") {
		Hit_Object.Set_HP(Hit_Object.Get_HP() - 25);
		this->arms_skill_count--;

		if (Hit_Object.Get_HP() == 0) return Wings_end;
		else return 25; // 데미지 리턴
	}
	else if (this->arms == "CatArms") {
		Hit_Object.Set_HP(Hit_Object.Get_HP() - 40);
		this->arms_skill_count--;

		if (Hit_Object.Get_HP() == 0) return Cat_end;
		else return 40; // 데미지 리턴
	}
	else if (this->arms == "ICArms") {
		if (this->Get_HP() + 15 > 50) this->Set_HP(50);
		else this->Set_HP(this->Get_HP() + 15);
		this->arms_skill_count--;
		
	}
	else {
		return false;
	}
	return false;
}

// 공주(보스) 구현

Boss::Boss() : Character(150, 0, 0) {
	this->last_bossattack = 0;
	this->boss_skill_list[0] = "손목 때리기";
	this->boss_skill_list[1] = "육두문자";
	this->boss_skill_list[2] = "침 뱉기";
	this->boss_skill_list[3] = "술주정";
}

int Boss::Skill_Attack(Character& Hit_Object, bool is_defense) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 3);

	this->last_bossattack = dist(gen);

	int attackDamage = 0;

	if (last_bossattack == 0) {

		attackDamage = 5 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 1) {
		attackDamage = 3 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 2) {
		attackDamage = 10 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 3) {
		this->Set_AttackDamage(this->Get_AttackDamage() + 2);
		return 0;
	}

	if (is_defense == true) {
		attackDamage /= 2;
		if (Hit_Object.Get_Shield() > 0) {
			if (Hit_Object.Get_Shield() >= attackDamage) Hit_Object.Set_Shield(Hit_Object.Get_Shield() - attackDamage);
			else {
				Hit_Object.Set_HP(Hit_Object.Get_HP() - (attackDamage - Hit_Object.Get_Shield()));
				Hit_Object.Set_Shield(0);
			}
		}
		else
			Hit_Object.Set_HP(Hit_Object.Get_HP() - attackDamage);
	}
	else {
		if (Hit_Object.Get_Shield() > 0) {
			if (Hit_Object.Get_Shield() >= attackDamage) Hit_Object.Set_Shield(Hit_Object.Get_Shield() - attackDamage);
			else {
				Hit_Object.Set_HP(Hit_Object.Get_HP() - (attackDamage - Hit_Object.Get_Shield()));
				Hit_Object.Set_Shield(0);
			}
		}
		else {
			Hit_Object.Set_HP(Hit_Object.Get_HP() - attackDamage);
		}
	}

	return attackDamage;

}

std::string Boss::Get_Last_Attack_Name() {
	return this->boss_skill_list[this->last_bossattack];
}
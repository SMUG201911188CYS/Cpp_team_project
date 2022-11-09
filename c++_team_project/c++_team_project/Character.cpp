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

int Character::normal_attack(Character& Hit_Object) {
	int damage = Hit_Object.Get_Shield() - attackDamage;
	if (damage >= 0) Hit_Object.Set_Shield(damage); // 쉴드가 더 높으면 쉴드에서 까고, 더 낮으면 쉴드는 0, 피를 깜
	else {
		Hit_Object.Set_Shield(0);
		Hit_Object.Set_HP(Hit_Object.Get_HP() - damage);
	}
	return attackDamage;
}

// 도리베어(플레이어) 구현

Player::Player() {
	this->arms = "없음";
	this->skill_discription = "없음";
	this->arms_skill_count = 0;
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
		this->skill_discription = "회오리로 적을 가둡니다. 해당 스킬로 처치시...";
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
		this->skill_discription = "냥냥펀치를 사용합니다. 해당 스킬로 처치시...";
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

int Player::Skill_Attack(Character& Hit_Object) {
	
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
}

// 공주(보스) 구현

Boss::Boss() {
	Set_HP(200);
	Set_AttackDamage(0);
	this->last_bossattack = 0;
	this->boss_skill_list[0] = "손목 때리기";
	this->boss_skill_list[1] = "육두문자";
	this->boss_skill_list[2] = "침 뱉기";
	this->boss_skill_list[3] = "술주정";
}

int Boss::Skill_Attack(Character & Hit_Object) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(0, 3);

	this->last_bossattack = dist(gen);

	if (last_bossattack == 0) {
		Hit_Object.Set_HP(Hit_Object.Get_HP() - 5 + this->Get_AttackDamage());
		return 5 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 1) {
		Hit_Object.Set_HP(Hit_Object.Get_HP() - 3 + this->Get_AttackDamage());
		return 3 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 2) {
		Hit_Object.Set_HP(Hit_Object.Get_HP() - 10 + this->Get_AttackDamage());
		return 10 + this->Get_AttackDamage();
	}
	else if (last_bossattack == 3) {
		this->Set_AttackDamage(this->Get_AttackDamage() + 2);
		return 0;
	}
}

std::string Boss::Get_Last_Attack_Name() {
	return this->boss_skill_list[this->last_bossattack];
}
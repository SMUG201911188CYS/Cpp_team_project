#include "enum.h"

Item::Item() {
	item = "없음";
	item_effect = "   ";
}

bool Item::init_item(int item) { // 아이템 얻을 시 초기화
	
	if (item == CHEWING_GUM) {
		this->item = "껌";
		this->item_effect = "보호막을 10 얻습니다.";
	}
	else if (item == COTTON) {
		this->item = "솜뭉치";
		this->item_effect = "체력을 10 회복합니다.";
	}
	else if (item == INSSA_RABBIT) {
		this->item = "인싸 토끼";
		this->item_effect = "보스의 공격력이 감소합니다.";
	}
	else if (item == MAGIC_CIRCLE) {
		this->item = "매직 서클";
		this->item_effect = "보스에게 50의 데미지를 입힙니다.";
	}
	else if (item == F_GRADE_CARD) {
		this->item = "F맞은 성적표";
		this->item_effect = "F맞은 성적표를 던집니다.";
	}
	else if (item == INF_GAUNTLETS) {
		this->item = "인피니티 건틀릿";
		this->item_effect = "둘 중 한명은 사라집니다.";
	}
	else if (item == MEET_IC) {
		this->item = "아이스크림";
		this->item_effect = "체력을 20 회복합니다.";
	}
	else if (item == NONE) {
		this->item = "없음";
		this->item_effect = "    ";
	}
	else if (item == EXIT) {
		this->item = "가방 닫기";
		this->item_effect = "    ";
	}
	else {
		this->item = "없음";
		this->item_effect = "    ";
	}

	return true;
}

int Item::use_item(Character & player, Character & boss) {

	if (item == "없음") {
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("아이템이 없습니다.");
		Sleep(1500);

		return false;
	}
	if (item == "가방 닫기") {
		return EXIT;
	}
	else if (item == "껌") { // 사용하면 보호막 10 증가
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("껌을 사용했습니다!");
		Sleep(1500);
		control.gotoxy(65, 48);
		printf("보호막 10을 얻었습니다!");
		Sleep(1500);
		int shield = player.Get_Shield();
		player.Set_Shield(CHEWING_GUM_SHIELD + shield);
	}
	else if (item == "솜뭉치") { // 사용하면 피 10 회복
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("솜뭉치를 사용했습니다!");
		Sleep(1500);
		control.gotoxy(65, 48);
		printf("피 10을 회복했습니다!  ");
		Sleep(1500);
		int hp = player.Get_HP();
		if (hp + COTTON_HEAL >= PLAYER_HP) player.Set_HP(PLAYER_HP);
		else player.Set_HP(COTTON_HEAL + hp);
	}
	else if (item == "아이스크림") { // 사용하면 피 20 회복
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("아이스크림을 사용했습니다!");
		Sleep(1500);
		control.gotoxy(65, 48);
		printf("피 20을 회복했습니다!  ");
		Sleep(1500);
		int hp = player.Get_HP();
		if (hp + ICREAM_HEAL >= PLAYER_HP) player.Set_HP(PLAYER_HP);
		else player.Set_HP(ICREAM_HEAL + hp);
	}
	else if (item == "인싸 토끼") { // 사용하면 보스 공격력 1 감소
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("인싸토끼모자를 사용했습니다!");
		Sleep(1500);
		control.gotoxy(65, 48);
		printf("공주의 공격력이 2 감소했습니다!");
		Sleep(1500);
		int boss_ad = boss.Get_AttackDamage();
		boss.Set_AttackDamage(boss_ad - INSSA_RABBIT_DM_DOWN);
	}
	else if (item == "매직 서클") {
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("매직서클을 사용했습니다!");
		Sleep(1500);
		control.gotoxy(65, 48);
		printf("공주에게 50의 데미지를 입혔습니다!");
		Sleep(1500);

		int boss_hp = boss.Get_HP(); // 사용하면 보스 피 50 감소
		boss.Set_HP(boss_hp - MAGIC_CIRCLE_DM);
	}
	else if (item == "F맞은 성적표") { // 사용하면 보스 공격력이 5증가 or c뿌리기 패시브가 있으면 히든엔딩
		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("F맞은 성적표를 사용했습니다!");
		Sleep(1500);

		if (boss.Get_Passive() == F_GRADE_CARD_END)
			return F_GRADE_CARD_END;
		else {
			int boss_ad = boss.Get_AttackDamage();
			boss.Set_AttackDamage(boss_ad + F_GRADE_CARD_DM_UP);
		}
	}
	else if (item == "인피니티 건틀릿") { // 사용하면 보스 or 플레이어 둘중에 한명 사망, 히든 엔딩
		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<> dist(0, 1);

		control.gotoxy(65, 47);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("                                         ");
		control.gotoxy(65, 49);
		printf("                                         ");
		control.gotoxy(65, 50);
		printf("                                         ");
		control.gotoxy(65, 48);
		printf("인피니티 건틀릿을 사용했습니다!");
		Sleep(1500);

		if (dist(gen) == 0) return INF_GAUNTLETS_END1;
		else return INF_GAUTTLETS_END2;
	}
	else {
		return false;
	}


	init_item(NONE);
	return true;
}

std::string Item::get_item_name() {

	return this->item;
}

std::string Item::get_item_effect() {

	return this->item_effect;

}
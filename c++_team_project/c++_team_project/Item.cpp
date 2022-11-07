#include "Item.h"

Item::Item() {
	item = "없음";
	item_effect = "   ";
}

bool Item::init_item(int item) {
	
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
	else {
		this->item = "없음.";
		this->item_effect = "    ";
	}

	return true;
}

int Item::use_item() {

	if (item == "없음") return 101;
	else if (item == "껌") return 10;
	else if (item == "인싸 토끼") return 1;
	else if (item == "매직 서클") return 50;
	else if (item == "F맞은 성적표") return 102;
	else if (item == "인피니티 건틀릿") return 103;

}
#ifndef __ITEM_H__

#define __ITEM_H__
#include <vector>
#include <string>
#include "Character.h"
#include <random>

class Item {
private:
	std::string item;
	std::string item_effect;
	enum item_list { // 아이템 리스트
		CHEWING_GUM,
		COTTON,
		INSSA_RABBIT = 3,
		INF_GAUNTLETS = 4,
		MAGIC_CIRCLE = 5,
		F_GRADE_CARD = 6,
		NONE = 11
	};
	enum item_effect_list { // 아이템 효과
		CHEWING_GUM_SHIELD = 10, // 피 10 회복
		COTTON_HEAL = CHEWING_GUM_SHIELD, // 피 10 회복
		INSSA_RABBIT_DM_DOWN = 1, // 공격력 1 감소
		MAGIC_CIRCLE_DM = 50, // 50의 데미지 입힘
		F_GRADE_CARD_DM_UP = 5, // 공격력 5 상승
		PLAYER_HP = 50, // 플레이어 기본 hp
		BOSS_HP = 200, // 보스 기본 hp
		F_GRADE_CARD_END = 312, // 엔딩
		INF_GAUNTLETS_END1 = 314, // 엔딩
		INF_GAUTTLETS_END2 = 315 // 엔딩
	};
public:
	Item();
	bool init_item(int item);
	int use_item(Character & character);
	std::string get_item_name();
	std::string get_item_effect();
};


#endif // !__ITEM_H__

#ifndef __EMUM_H__

#define __EMUM_H__

#include <iostream>
#include <string>
#include <random>
#include <conio.h>
#include <vector>
#include <Windows.h>

#include "Control.h"
#include "Scene.h"
#include "Ending.h"
#include "Room.h"
#include "Event.h"
#include "Character.h"
#include "Item.h"
#include "Bag.h"

enum keboard { // 키 입력 enum
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SUBMIT,
	START = 24,
	EXIT = 31,
	L = 50,
	M = 51,
	R = 52
};

enum item_effect_list { // 아이템 효과
	CHEWING_GUM_SHIELD = 10, // 피 10 회복
	CHEESE_SHIELD = CHEWING_GUM_SHIELD,
	ICREAM_HEAL = 20, // 피 20 회복
	COTTON_HEAL = CHEWING_GUM_SHIELD, // 피 10 회복
	INSSA_RABBIT_DM_DOWN = 2, // 공격력 2 감소
	MAGIC_CIRCLE_DM = 50, // 50의 데미지 입힘
	F_GRADE_CARD_DM_UP = 5, // 공격력 5 상승
	PLAYER_HP = 50, // 플레이어 기본 hp
	BOSS_HP = 200, // 보스 기본 hp
	F_GRADE_CARD_END = 312, // 엔딩
	INF_GAUNTLETS_END1 = 314, // 엔딩
	INF_GAUTTLETS_END2 = 315 // 엔딩
};

enum passive {
	DEADHARD = 7,
	FARMING = 11,
	LISTEN = 14
};
enum item_list { // 아이템 이름
	CHEWING_GUM,
	COTTON,
	NONE,
	INSSA_RABBIT,
	INF_GAUNTLETS,
	MAGIC_CIRCLE,
	F_GRADE_CARD,
	GET_DEADHARD,
	GET_CHEESE,
	MATH,
	TAGD,
	GET_FARMING,
	MEET_IC,
	MEET_HOMELESS,
	GET_LISTEN,
	GET_DoriArms,
	GET_Wings,
	GET_Twigs,
	GET_CatArms,
	GET_BarbieArms,
	GET_ICArms,
};

enum Arms {
	Dori_Bear_arms = 15,
	Wings = 16,
	Twigs = 17,
	CatArms = 18,
	BarbieArms = 19,
	ICArms = 20,
	Wings_end = 412,
	Cat_end = 414,
};

enum object { // 방 내부 오브젝트 목록들 enum
	pot,
	box,
	hole,
	bookshelf,
	circle,
	paper,
	button,
	mouse,
	npc,
	pipe,
	lake
};

enum num {
	FIRST,
	SECOND,
	THIRD
};

#endif // !__EMUM_H__


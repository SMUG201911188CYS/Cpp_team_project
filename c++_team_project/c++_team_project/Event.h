#ifndef __EVENT_H__


#define __EVENT_H__
#include "Control.h"
#include <random>

class Event {
private:
	int rand_value;
	Control control;
	enum keboard {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SUBMIT
	};

	enum Event_percent {
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
	int pot_item_percent[10] = { 0,0,0,0,1,1,1,1,2,2 };
	int box_item_percent[10] = { 0,0,1,1,2,2,3,3,3,4 };
	int circle_item_percent[10] = { 2, 2, 2, 2, 5, 5, 5, 5, 5, 5 };
	int paper_item_percent[10] = { 2, 2, 2, 2, 6, 6, 6, 6, 6, 6 };
	int button_tiem_percent[10] = { 2, 2, 2, 2, 2, 2, 7, 7, 7, 7 };
	int mouse_item_percent[10] = { 2, 2, 2, 2, 2, 2, 8, 8, 8, 8 };
	int book_item_percent[10] = { 9, 9, 9, 10, 10, 10, 11, 11, 11, 11 };
	int npc_item_percent[10] = { 12, 12, 12, 12, 12, 12, 13, 13, 13, 13 };

public:
	Event();
	int rand();
	int pot();
	int box();
	int hole();
	int bookshelf();
	int circle();
	int paper();
	int button();
	int mouse();
	int book();
	int npc(int sewer_in);
	int pipe(int sewer_in);
	int lake(int sewer_in);
};



#endif // !__EVENT_H__

#ifndef __EVENT_H__


#define __EVENT_H__
#include "enum.h"

class Event {
private:
	int rand_value;
	Control control;
	int pot_item_percent[10] = { 0,0,0,0,1,1,1,1,2,2 }; // 각 이벤트 확률 -> item_list과 동일
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
	int npc(int sewer_in);
	int pipe(int sewer_in);
	int lake(int sewer_in);
};



#endif // !__EVENT_H__

#ifndef __ROOM_H__

#define __ROOM_H__

#include "enum.h"

class Room : public Control {
private:
	int x;
	int y;
	int sewer_in; // 처음 하수구 선택 1 -> C 2 -> G417, 3 -> NORMAL
	int cross_in[3];

public:
	Room();
	bool intro();
	bool sewer();
	bool crossroad();
	int c_room1_1();
	int c_room1_2();
	int c_room1_3();
	int c_room2_1();
	int c_room2_2();
	int c_room2_3();
	int c_room3_1();
	int c_room3_2();
	int c_room3_3();
	int g_room1_1();
	int g_room1_2();
	int g_room1_3();
	int g_room2_1();
	int g_room2_2();
	int g_room2_3();
	int g_room3_1();
	int g_room3_2();
	int g_room3_3();
	int n_room1_1();
	int n_room1_2();
	int n_room1_3();
	int n_room2_1();
	int n_room2_2();
	int n_room2_3();
	int n_room3_1();
	int n_room3_2();
	int n_room3_3();
	int Get_Sewer_in();
	int Get_Crossroad_In(int index);
};

#endif // !__ROOM_H__

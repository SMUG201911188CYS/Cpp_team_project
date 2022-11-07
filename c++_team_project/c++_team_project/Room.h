#ifndef __ROOM_H__

#define __ROOM_H__
#include "Control.h"
class Room {
private:
	int x;
	int y;
	Control control;
	int intro_in; // 게임시작 or 게임종료 선택
	int sewer_in; // 처음 하수구 선택 1 -> C 2 -> G417, 3 -> NORMAL
	int first_crossroad_in;
	int second_crossroad_in;
	int third_crossroad_in;
	enum choice {
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
	enum object {
		pot,
		box,
		hole,
		bookshelf,
		circle,
		paper,
		button,
		mouse,
		book,
		npc,
		pipe,
		lake
	};
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
};

#endif // !__ROOM_H__

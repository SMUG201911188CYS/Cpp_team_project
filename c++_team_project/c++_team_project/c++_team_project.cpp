#include <iostream>
#include <Windows.h>
#include "Control.h"
#include "Scene.h"
#include "Ending.h"
#include "Room.h"
#include "Event.h"

int main()
{
    system("mode con cols=150 lines=55 | title 도리 베어");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

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

	Scene scene;
	Room room;
	Event event;

	scene.show_room();
	int r = room.c_room1_1();

	if (r == pot) {
		int a = event.pot();
		std::cout << a;
	}
	else if (r == box) {
		int b = event.box();
		std::cout << b;
	}
	else if (r == hole) {
		int a = event.hole();
		std::cout << a;
	}


	return 0;
}
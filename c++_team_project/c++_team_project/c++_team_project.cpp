#include <iostream>
#include <Windows.h>
#include "Control.h"
#include "Scene.h"
#include "Ending.h"
#include "Room.h"
#include "Event.h"
#include "Character.h"
#include "Item.h"

int main()
{
    system("mode con cols=150 lines=55 | title 도리 베어");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	Character A(100, 10, 10);
	Item B;
	enum item_list {
		CHEWING_GUM,
		COTTON,
		INSSA_RABBIT = 3,
		INF_GAUNTLETS = 4,
		MAGIC_CIRCLE = 5,
		F_GRADE_CARD = 6,
	};
	std::cout << "hp >> " << A.Get_HP() << std::endl;
	std::cout << "shiel >> " << A.Get_Shield() << std::endl;
	std::cout << "ad >> " << A.Get_AttackDamage() << std::endl;
	std::cout << "passive >> " << A.Get_Passive() << std::endl;
	B.init_item(F_GRADE_CARD);
	std::cout << "USE " << B.get_item_name() << ", Effect " << B.get_item_effect() << std::endl;
	B.use_item(A);
	std::cout << "After USE " << B.get_item_name() << ", Effect " << B.get_item_effect() << std::endl;

	std::cout << "hp >> " << A.Get_HP() << std::endl;
	std::cout << "shiel >> " << A.Get_Shield() << std::endl;
	std::cout << "ad >> " << A.Get_AttackDamage() << std::endl;
	std::cout << "passive >> " << A.Get_Passive() << std::endl;
	return 0;
}
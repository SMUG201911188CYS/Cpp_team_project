#include "enum.h"
#include "Game.h"

int main()
{
    system("mode con cols=150 lines=55 | title 도리 베어");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	Game game;

	while (true) {
		/*bool do_end = game.game();
		if (do_end == false) {
			system("cls");
			std::cout << "바이바이";
			break;
		}*/
		game.battle(game.battle_check());
		system("cls");
	}

	return 0;
}
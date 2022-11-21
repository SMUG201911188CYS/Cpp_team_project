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

	int mode_choose = 0;
	bool game1_end = true;
	bool game2_end = true;

	while (1) {
		std::cout << "어떤 모드로 할건지 입력" << std::endl;
		std::cout << "1. 스토리 모드 // 2. 보스전만" << std::endl;
		std::cout << ">>";
		std::cin >> mode_choose;
		system("cls");
		if (mode_choose == 1) {
			game1_end = true;
			while (game1_end) {
				Game game1;
				bool do_end = game1.game();
				if (do_end == false) {
					system("cls");
					std::cout << "바이바이";
					return 0;
				}
				game1.battle(game1.battle_check());
				system("cls");
				game1_end = false;
			}
		}
		else if (mode_choose == 2) {
			game2_end = true;
			while (game2_end) {
				Game game2;
				game2.test_setting();
				game2.battle(game2.battle_check());
				game2_end = false;
			}
		}
		else {
			std::cout << "다시 입력" << std::endl;
		}
	}

	return 0;
}
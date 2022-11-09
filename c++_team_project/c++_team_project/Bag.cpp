#include "Bag.h"
#include "Character.h"
#include "Item.h"


Bag::Bag() {
	bag_item[3].init_item(EXIT); // 가방의 네번째 칸은 가방 닫기
	bag_size = 0;
}

bool Bag::input_item(int item) {
	return this->bag_item[bag_size++].init_item(item);
}

void Bag::bag_list_print() {
	control.gotoxy(65, 50);
	printf("                                     ");
	control.gotoxy(65, 51);
	printf("                                     ");
	control.gotoxy(65, 52);
	printf("                                     ");
	control.gotoxy(65, 48);
	printf("가방을 열어 아이템을 사용한다!");
	control.gotoxy(65, 50);
	printf("                                     ");
	control.gotoxy(65, 51);
	printf("                                     ");
	control.gotoxy(65, 52);
	printf("                                     ");
	control.gotoxy(65, 49);
	printf("보유 아이템");
	control.gotoxy(65, 50);
	std::cout.width(10);
	std::cout << std::left << bag_item[0].get_item_name();
	control.gotoxy(75, 50);
	std::cout.width(10);
	std::cout << std::left << bag_item[0].get_item_name();
	control.gotoxy(85, 50);
	std::cout.width(10);
	std::cout << std::left << bag_item[0].get_item_name();
}

int Bag::bag_open(Character & player, Character & boss) {
	control.gotoxy(65, 47);
	printf("                               ");
	control.gotoxy(65, 48);
	printf("                               ");
	control.gotoxy(65, 49);
	printf("                               ");
	control.gotoxy(65, 50);
	printf("                                          ");
	control.gotoxy(115, 47);
	printf("                                 ");
	control.gotoxy(115, 50);
	printf("                                ");
	int x = 115;
	int y = 47;
	control.gotoxy(x, y);
	std::cout << "▶ " << bag_item[0].get_item_name();
	control.gotoxy(x - 50, y);
	std::cout << bag_item[0].get_item_effect();
	control.gotoxy(x, y + 1);
	std::cout << "   " << bag_item[1].get_item_name();
	control.gotoxy(x, y + 2);
	std::cout << "   " << bag_item[2].get_item_name();
	control.gotoxy(x, y + 3);
	std::cout << "   " << bag_item[3].get_item_name();

	while (1)
	{
		int n = control.key_control();
		switch (n) {
		case UP:
		{
			if (y > 47)
			{
				control.gotoxy(x, y);
				printf("   ");
				control.gotoxy(x, y - 1);
				printf("▶");
				y = y - 1;
			}
			break;
		}
		case DOWN:
		{
			if (y < 50)
			{
				control.gotoxy(x, y);
				printf("   ");
				control.gotoxy(x, y + 1);
				printf("▶");
				y = y + 1;
			}
			break;
		}
		case SUBMIT:
		{
			if (y == 47)
			{
				return bag_item[0].use_item(player, boss);
			}
			else if (y == 48)
			{
				return bag_item[1].use_item(player, boss);
			}
			else if (y == 49)
			{
				return bag_item[2].use_item(player, boss);
			}
			else if (y == 50)
			{
				return bag_item[3].use_item(player, boss);
			}
		}
		}
		if (y == 47)
		{
			control.gotoxy(x - 50, 48);
			printf("                                           ");
			control.gotoxy(x - 50, 49);
			printf("                                           ");
			control.gotoxy(x - 50, 47);
			std::cout << bag_item[0].get_item_effect();
		}
		else if (y == 48)
		{
			control.gotoxy(x - 50, 47);
			printf("                                           ");
			control.gotoxy(x - 50, 49);
			printf("                                           ");
			control.gotoxy(x - 50, 48);
			std::cout << bag_item[1].get_item_effect();
		}
		else if (y == 49)
		{
			control.gotoxy(x - 50, 47);
			printf("                                           ");
			control.gotoxy(x - 50, 48);
			printf("                                           ");
			control.gotoxy(x - 50, 49);
			std::cout << bag_item[2].get_item_effect();
		}
		else if (y == 50)
		{
			control.gotoxy(x - 50, 47);
			printf("                                           ");
			control.gotoxy(x - 50, 48);
			printf("                                           ");
			control.gotoxy(x - 50, 49);
			std::cout << bag_item[3].get_item_effect();
		}
	}
	control.gotoxy(x - 50, 47);
	printf("                                           ");
	control.gotoxy(x - 50, 48);
	printf("                                           ");
	control.gotoxy(x - 50, 49);
	printf("                                           ");
	control.gotoxy(x - 50, 50);
	printf("                                           ");
}
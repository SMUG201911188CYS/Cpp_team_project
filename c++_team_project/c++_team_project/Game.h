#ifndef __GAME_H__

#define __GAME_H__

#include "enum.h"

class Game {
private:
	Control control;
	Scene scene;
	Ending end;
	Room room;
	Event event;
	Bag player_bag;
	Player dori_bear;
	Boss princess;
public:
	bool game();
	bool battle(bool do_battle);
	bool battle_check() {
		if (this->dori_bear.Get_Arms() == "¾øÀ½") return false;
		else return true;
	}
	void hp_print();
	void menu_print();
	void boss_turn();
	void test_setting();
};

#endif // !__GAME_H__

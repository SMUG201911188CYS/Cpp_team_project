#ifndef __GAME_H__

#define __GAME_H__

#include "enum.h"

class Game {
private:
	Control control;
	Scene scene;
	Room room;
	Event event;
	Bag player_bag;
	Character player;
	Character boss;
public:
	bool game();
	bool battle();
};

#endif // !__GAME_H__

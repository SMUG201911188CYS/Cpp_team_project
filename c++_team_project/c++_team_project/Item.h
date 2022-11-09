#ifndef __ITEM_H__

#define __ITEM_H__

#include "enum.h"

class Item {
private:
	std::string item;
	std::string item_effect;
	Control control;
public:
	Item();
	bool init_item(int item);
	int use_item(Character & player, Character & boss);
	std::string get_item_name();
	std::string get_item_effect();
};


#endif // !__ITEM_H__

#ifndef __BAG_H__

#define __BAG_H__

#include "enum.h"

class Bag {
private:
	Control control;
	Item bag_item[4];
	int bag_size;
public:
	Bag();
	bool input_item(int item);
	int bag_open(Character & player, Character & boss);
	void bag_list_print();
};

#endif // ! __BAG_H__

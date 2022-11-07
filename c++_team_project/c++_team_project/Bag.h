#ifndef  __BAG_H__

#define __BAG_H__
#include "Item.h"
#include "Control.h"
class Bag {
private:
	Control control;
	Item bag_item[4];
public:
	Bag();
	bool bag_print();
	void bag_list();
};

#endif // ! __BAG_H__

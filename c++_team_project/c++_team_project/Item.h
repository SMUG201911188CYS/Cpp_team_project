#ifndef __ITEM_H__

#define __ITEM_H__
#include <vector>
#include <string>

class Item {
private:
	std::string item;
	std::string item_effect;
	enum item_list {
		CHEWING_GUM,
		COTTON,
		INSSA_RABBIT = 3,
		INF_GAUNTLETS = 4,
		MAGIC_CIRCLE = 5,
		F_GRADE_CARD = 6,
		MATH = 9,
		TAGD = 10,
	};
public:
	Item();
	bool init_item(int item);
	int use_item();
	std::string get_item_name(int i);
	std::string get_item_effect(int i);
};


#endif // !__ITEM_H__

#ifndef __Scene_h__
#define __Scene_h__
#include "Control.h"

class Scene {
protected:
	Control control;
public:
	void text_color_change (int color_number); // 텍스트 색 변경
	void show_StartIntro();
	void show_MainIntro();
	void show_Scenario();
	void show_Sewer();
	void show_crossroads();
	void show_room();
	void show_BossIntro();
	void show_Boss();
};

#endif // !__Scene_h__

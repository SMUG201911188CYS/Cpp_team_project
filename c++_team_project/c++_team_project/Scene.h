#ifndef __Scene_h__
#define __Scene_h__
#include "Control.h"

class Scene {
protected:
	Control control;
public:
	void text_color_change (int color_number); // 텍스트 색 변경
	void show_StartIntro(); // 시작 화면
	void show_MainIntro(); // 메인 화면
	void show_Scenario(); // 시나리오 화면
	void show_Sewer(); // 하수구 화면
	void show_crossroads(); // 갈림길 화면
	void show_room(); // 방 화면
	void show_BossIntro(); // 보스전 입장 화면
	void show_Boss(); // 보스전 화면
};

#endif // !__Scene_h__

#include "Game.h"
#include "enum.h"

bool Game::game() {

	int what_Event = NONE;
	int get_1 = NONE;
	int get_2 = NONE;
	int get_3 = NONE;

	scene.show_StartIntro();
	scene.show_MainIntro();

	int main = room.intro();
	if (main == false) return false;

	scene.show_Scenario();

	scene.show_Sewer();
	room.sewer();

	scene.show_crossroads();
	room.crossroad();

	scene.show_room();

	if (room.Get_Sewer_in() == 1) { // C많은 하수구
		// 첫번째 갈림길
		if (room.Get_Crossroad_In(FIRST) == 1) what_Event = room.c_room1_1(); // 항아리, 상자, 구덩이
		else if (room.Get_Crossroad_In(FIRST) == 2) what_Event = room.c_room1_2(); // 종이조각, 항아리, 구덩이
		else if (room.Get_Crossroad_In(FIRST) == 3) what_Event = room.c_room1_3(); // 종이조각, 상자, 항아리

		// 이벤트 처리
		if (what_Event == pot) get_1 = event.pot();
		else if (what_Event == box) get_1 = event.box();
		else if (what_Event == paper) get_1 = event.paper();
		else if (what_Event == hole) get_1 = event.hole();
		else get_1 = NONE;


		scene.show_crossroads();
		room.crossroad();

		//두번째 갈림길
		scene.show_room();
		if (room.Get_Crossroad_In(SECOND) == 1) what_Event = room.c_room2_1();  // 이상한 사람, 책장, 항아리
		else if (room.Get_Crossroad_In(SECOND) == 2) what_Event = room.c_room2_2(); // 상자, 책장, 항아리
		else if (room.Get_Crossroad_In(SECOND) == 3) what_Event = room.c_room2_3(); // 구덩이

		// 이벤트 처리
		if (what_Event == pot) get_2 = event.pot();
		else if (what_Event == npc) get_2 = event.npc(room.Get_Sewer_in());
		else if (what_Event == bookshelf) get_2 = event.bookshelf();
		else if (what_Event == hole) get_2 = event.hole();
		else get_2 = NONE;

		scene.show_crossroads();
		room.crossroad();

		//세번째 갈림길
		scene.show_room();
		if (room.Get_Crossroad_In(THIRD) == 1) what_Event = room.c_room3_1(); // 파이프, 쥐구멍, 항아리
		else if (room.Get_Crossroad_In(THIRD) == 2) what_Event = room.c_room3_2();// 고인물, 쥐구멍, 항아리
		else if (room.Get_Crossroad_In(THIRD) == 3) what_Event = room.c_room3_3(); // 종이조각, 구덩이, 항아리

		// 이벤트 처리
		if (what_Event == pot) get_3 = event.pot();
		else if (what_Event == pipe) get_3 = event.pipe(room.Get_Sewer_in());
		else if (what_Event == lake) get_3 = event.lake(room.Get_Sewer_in());
		else if (what_Event == paper) get_3 = event.paper();
		else if (what_Event == mouse) get_3 = event.mouse();
		else if (what_Event == hole) get_3 = event.hole();
		else get_1 = NONE;

	}
	else if (room.Get_Sewer_in() == 2) { // G417 하수구 

		if (room.Get_Crossroad_In(FIRST) == 1) what_Event = room.g_room1_1(); // 상자, 구덩이, 종이조각
		else if (room.Get_Crossroad_In(FIRST) == 2) what_Event = room.g_room1_2(); // 쥐구멍, 항아리, 구덩이
		else if (room.Get_Crossroad_In(FIRST) == 3) what_Event = room.g_room1_3(); // 구덩이

		// 이벤트 처리
		if (what_Event == pot) get_1 = event.pot();
		else if (what_Event == box) get_1 = event.box();
		else if (what_Event == paper) get_1 = event.paper();
		else if (what_Event == hole) get_1 = event.hole();
		else if (what_Event == mouse) get_1 = event.mouse();
		else get_1 = NONE;

		scene.show_crossroads();
		room.crossroad();

		//두번째 갈림길
		scene.show_room();

		if (room.Get_Crossroad_In(SECOND) == 1) what_Event = room.g_room2_1(); // 이상한 원, 상자, 구덩이
		else if (room.Get_Crossroad_In(SECOND) == 2) what_Event = room.g_room2_2(); // 이상한 사람, 항아리, 상자
		else if (room.Get_Crossroad_In(SECOND) == 3) what_Event = room.g_room2_3(); // 이상한 사람, 이상한 원, 구덩이

		// 이벤트 처리
		if (what_Event == pot) get_2 = event.pot();
		else if (what_Event == npc) get_2 = event.npc(room.Get_Sewer_in());
		else if (what_Event == circle) get_2 = event.circle();
		else if (what_Event == box) get_2 = event.box();
		else if (what_Event == hole) get_2 = event.hole();
		else get_2 = NONE;

		scene.show_crossroads();
		room.crossroad();

		//세번째 갈림길
		scene.show_room();

		if (room.Get_Crossroad_In(THIRD) == 1) what_Event = room.g_room3_1(); // 파이프, 쥐구멍, 구덩이
		else if (room.Get_Crossroad_In(THIRD) == 2) what_Event = room.g_room3_2(); // 고인물, 쥐구멍, 상자
		else if (room.Get_Crossroad_In(THIRD) == 3) what_Event = room.g_room3_3(); // 종이조각, 구덩이, 항아리

		// 이벤트 처리
		if (what_Event == pot) get_3 = event.pot();
		else if (what_Event == pipe) get_3 = event.pipe(room.Get_Sewer_in());
		else if (what_Event == lake) get_3 = event.lake(room.Get_Sewer_in());
		else if (what_Event == paper) get_3 = event.paper();
		else if (what_Event == mouse) get_3 = event.mouse();
		else if (what_Event == box) get_3 = event.box();
		else if (what_Event == hole) get_3 = event.hole();
		else get_1 = NONE;

	}
	else if (room.Get_Sewer_in() == 3) { // 그냥 하수구

		if (room.Get_Crossroad_In(FIRST) == 1) what_Event = room.n_room1_1(); // 종이조각, 상자, 구덩이
		else if (room.Get_Crossroad_In(FIRST) == 2) what_Event = room.n_room1_2(); // 쥐구멍, 항아리, 구덩이
		else if (room.Get_Crossroad_In(FIRST) == 3) what_Event = room.n_room1_3(); // 상자, 구덩이, 항아리

		// 이벤트 처리
		if (what_Event == pot) get_1 = event.pot();
		else if (what_Event == box) get_1 = event.box();
		else if (what_Event == paper) get_1 = event.paper();
		else if (what_Event == hole) get_1 = event.hole();
		else if (what_Event == mouse) get_1 = event.mouse();
		else get_1 = NONE;

		scene.show_crossroads();
		room.crossroad();

		//두번째 갈림길
		scene.show_room();

		if (room.Get_Crossroad_In(SECOND) == 1) what_Event = room.n_room2_1(); // 스위치, 구덩이, 이상한 사람
		else if (room.Get_Crossroad_In(SECOND) == 2) what_Event = room.n_room2_2(); // 상자, 스위치, 종이조각
		else if (room.Get_Crossroad_In(SECOND) == 3) what_Event = room.n_room2_3(); // 구덩이

		// 이벤트 처리
		if (what_Event == npc) get_2 = event.npc(room.Get_Sewer_in());
		else if (what_Event == box) get_2 = event.box();
		else if (what_Event == paper) get_2 = event.paper();
		else if (what_Event == hole) get_2 = event.hole();
		else if (what_Event == button) get_2 = event.button();
		else get_2 = NONE;


		scene.show_crossroads();
		room.crossroad();

		//세번째 갈림길
		scene.show_room();

		if (room.Get_Crossroad_In(THIRD) == 1) what_Event = room.n_room3_1(); // 파이프, 쥐구멍, 상자
		else if (room.Get_Crossroad_In(THIRD) == 2) what_Event = room.n_room3_2(); // 고인물, 쥐구멍, 구덩이
		else if (room.Get_Crossroad_In(THIRD) == 3) what_Event = room.n_room3_3(); // 쥐구멍, 구덩이, 항아리

		// 이벤트 처리
		if (what_Event == pot) get_3 = event.pot();
		else if (what_Event == pipe) get_3 = event.pipe(room.Get_Sewer_in());
		else if (what_Event == lake) get_3 = event.lake(room.Get_Sewer_in());
		else if (what_Event == mouse) get_3 = event.mouse();
		else if (what_Event == box) get_3 = event.box();
		else if (what_Event == hole) get_3 = event.hole();
		else get_1 = NONE;

	}

	// 1스테이지 오브젝트 목록 : 항아리, 상자, 종이조각, 쥐구멍, 구덩이
	
	if (get_1 == GET_CHEESE) dori_bear.Set_Shield(dori_bear.Get_Shield() + CHEESE_SHIELD);
	else if (get_1 == NONE) std::cout << "";
	else player_bag.input_item(get_1);

	
	// 2스테이지 오브젝트 목록 : 이상한 사람, 책장, 항아리, 상자, 구덩이, 이상한 원, 스위치

	if (get_2 == GET_DEADHARD) dori_bear.Set_Passive(DEADHARD);
	else if (get_2 == GET_FARMING) dori_bear.Set_Passive(FARMING);
	else if (get_2 == NONE) std::cout << "";
	else player_bag.input_item(get_2);

	// 3스테이지 오브젝트 목록 : 파이프, 쥐구멍, 항아리, 고인물, 종이조각, 구덩이, 상자

	if (get_3 == GET_CHEESE) dori_bear.Set_Shield(dori_bear.Get_Shield() + CHEESE_SHIELD);
	else if (get_3 == GET_Wings) dori_bear.Set_Arms(Wings);
	else if (get_3 == GET_CatArms) dori_bear.Set_Arms(CatArms);
	else if (get_3 == GET_DoriArms) dori_bear.Set_Arms(Dori_Bear_arms);
	else if (get_3 == GET_Twigs) dori_bear.Set_Arms(Twigs);
	else if (get_3 == GET_BarbieArms) dori_bear.Set_Arms(BarbieArms);
	else if (get_3 == GET_ICArms) dori_bear.Set_Arms(ICArms);

	scene.show_BossIntro();

	return true;
}

bool Game::battle(bool do_battle) {

	if (do_battle == false) {
		end.show_BadEnd01();
		return true;
	}
	else {
		scene.show_Boss();
	}


}

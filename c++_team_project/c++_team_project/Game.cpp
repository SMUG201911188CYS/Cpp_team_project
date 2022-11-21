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
		else if (what_Event == box) get_2 = event.box();
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
		else get_3 = NONE;

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
		else get_3 = NONE;

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
		else get_3 = NONE;

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

void Game::hp_print() {

	control.gotoxy(10, 5);
	std::cout << "                           ";
	control.gotoxy(10, 5);
	std::cout << "보스 HP : " << princess.Get_HP();
	control.gotoxy(10, 10);
	std::cout << "                           ";
	control.gotoxy(10, 10);
	std::cout << "플레이어 HP : " << dori_bear.Get_HP() + dori_bear.Get_Shield();

}

void Game::menu_print() {
	int x = 115;
	int y = 47;
	control.gotoxy(x, y);
	std::cout <<"▶ 기본공격";
	control.gotoxy(x - 50, y + 1);
	std::cout <<"공주에게 기본 공격을 가한다!";
	control.gotoxy(x, y + 3);
	std::cout <<"   특수공격";
	control.gotoxy(x + 15, y);
	std::cout <<"   방어하기";
	control.gotoxy(x + 15, y + 3);
	std::cout <<"   가방보기";
}

void Game::boss_turn() {

	int x = 115;
	int y = 47;

	int boss_attack_damage = princess.Skill_Attack(dori_bear, true);

	control.gotoxy(x - 50, y + 3);
	std::cout << "                                     ";
	control.gotoxy(x - 50, y + 1);
	std::cout << "                                     ";
	control.gotoxy(x - 50, y + 2);
	std::cout << "                                     ";
	control.gotoxy(x - 50, y + 1);
	std::cout << "공주가 " << princess.Get_Last_Attack_Name() << "를 시전했다!";
	Sleep(1500);

	if (boss_attack_damage == 0) {
		control.gotoxy(x - 50, y + 3);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 1);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 2);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 1);
		std::cout << "공주님의 공격력이 2 증가하였다!";
		Sleep(1500);
	}
	else {
		control.gotoxy(x - 50, y + 3);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 1);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 2);
		std::cout << "                                     ";
		control.gotoxy(x - 50, y + 1);
		std::cout << "도리베어는 " << boss_attack_damage << "의 피해를 입었다!";
		Sleep(1500);
	}
	hp_print();

}


bool Game::battle(bool do_battle) {
	std::string bossListen[8] = { "공주 : %&^$#%@!!# %!!!!!!","도리베어: (방어하기를 계속 해보자.)","공주 : $#^%$&*%^$^#" ,"도리베어: (방어하기를 계속 해보자.)","공주 : ㅆ>>>ㅡㅡㅢㅣ>>>>", "도리베어: (조금 진정된 것 같다),","공주 : 으>>>>>으으ㅡㅡㅇ>>>","도리베어: (흠..조금 더 기다려보자)" };
	int listen_cnt = 0;

	test_setting();
	do_battle = true;

	if (do_battle == false) {
		end.show_BadEnd01();
		return true;
	}
	else {
		scene.show_Boss();
	}

	int x = 115;
	int y = 47;
	hp_print();
	control.gotoxy(x, y);
	std::cout << "▶ 기본공격";
	control.gotoxy(x - 50, y + 1);
	std::cout << "공주에게 기본 공격을 가한다!";
	control.gotoxy(x, y + 3);
	std::cout << "   특수공격";
	control.gotoxy(x + 15, y);
	std::cout << "   방어하기";
	control.gotoxy(x + 15, y + 3);
	std::cout << "   가방보기";

	while (1) {
		int n = control.key_control();
		switch (n) {
		case UP: {
			if (y > 47)
			{
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, y - 3);
				std::cout << "▶";
				y = y - 3;
			}
			break;
		}
		case DOWN: {
			if (y < 50) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, y + 3);
				std::cout << "▶";
				y = y + 3;
			}
			break;
		}
		case LEFT: {
			if (x > 115) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x - 15, y);
				std::cout << "▶";
				x = x - 15;
			}
			break;
		}
		case RIGHT: {
			if (x < 130) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x + 15, y);
				std::cout << "▶";
				x = x + 15;
			}
			break;
		}
		case SUBMIT: {
			if (x == 115 && y == 47) { // 기본 공격
				control.gotoxy(x - 50, y + 3);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 1);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 2);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 1);
				std::cout << "도리베어는 일반 공격을 했다!";
				Sleep(1500);

				control.gotoxy(x - 50, y + 3);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 1);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 2);
				std::cout << "                                     ";
				control.gotoxy(x - 50, y + 1);
				std::cout << "공주님에게 " << dori_bear.normal_attack(princess) << "의 피해를 입혔다!";
				Sleep(1500);

				hp_print();

				boss_turn();
			}  // 일반 공격

			else if (x == 115 && y == 50) { // 특수공격
				if (dori_bear.Get_Arms() == "Wings")
				{
					if (dori_bear.Get_Skill_Count() > 0)
					{
						int end_check = dori_bear.Skill_Attack(princess, true);

						control.gotoxy(x - 50, y - 2);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 2);
						std::cout << "도리베어는 회오오오리를 썻다!";
						Sleep(1500);
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                         ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "공주에게 25의 피해를 주었다!";
						Sleep(1500);
						control.gotoxy(x - 50, y);
						std::cout << "공주는 풀이 죽어서 행동을 하지 못했다...";
						Sleep(1500);
						control.gotoxy(10, 5);
						std::cout << "             ";
						control.gotoxy(10, 5);
						hp_print();

						control.gotoxy(x - 50, y);
						std::cout << "                                         ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                         ";

						if (end_check == Wings_end)
						{
							Sleep(1500);
							system("cls");
							end.show_SPEnd04();
							return true;
						}
					}
				}
				else if (dori_bear.Get_Arms() == "CatArms")
				{
					if (dori_bear.Get_Skill_Count() > 0)
					{
						int end_check = dori_bear.Skill_Attack(princess, true);

						control.gotoxy(x - 50, y - 2);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 2);
						std::cout << "도리베어는 냥냥펀치를 썻다!";
						Sleep(1500);
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                         ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "공주에게 40의 피해를 주었다!";
						Sleep(1500);
						control.gotoxy(10, 5);
						std::cout << "             ";
						control.gotoxy(10, 5);

						hp_print();

						if (end_check == Cat_end)
						{
							Sleep(1500);
							system("cls");
							end.show_SPEnd05();
							return true;
						}

						boss_turn();
					}
				}
				else if (dori_bear.Get_Arms() == "ICArms") // 아이스크림 사용
				{
					if (dori_bear.Get_Skill_Count() > 0)
					{
						int end_check = dori_bear.Skill_Attack(princess, true);

						control.gotoxy(x - 50, y - 2);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 2);
						std::cout << "도리베어는 자기 팔을 먹었다!";
						Sleep(1500);
						control.gotoxy(x - 50, y - 1);
						std::cout << "                                         ";
						control.gotoxy(x - 50, y + 1);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y);
						std::cout << "                                          ";
						control.gotoxy(x - 50, y - 1);
						std::cout << "피를 15 회복 했다!";
						Sleep(1500);

						hp_print();

						boss_turn();

					}
				}
			}

			else if (x == 130 && y == 47) { // 방어하기
				control.gotoxy(x - 65, y + 3);
				std::cout << "                                     ";
				control.gotoxy(x - 65, y + 1);
				std::cout << "                                     ";
				control.gotoxy(x - 65, y + 2);
				std::cout << "                                     ";
				control.gotoxy(x - 65, y + 1);
				std::cout << "도리베어는 방어하기를 사용했다!";
				Sleep(1500);
				if (dori_bear.Get_Passive() == LISTEN)
				{
					if (listen_cnt >= 7)
					{
						system("cls");
						end.show_TrueEnd08();
						return true;
					}
					control.gotoxy(x - 65, y + 3);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 2);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << bossListen[listen_cnt];
					listen_cnt++;
					Sleep(1500);
					control.gotoxy(x - 65, y + 3);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 2);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << bossListen[listen_cnt];
					listen_cnt++;
					Sleep(1500);
					control.gotoxy(x - 65, y + 3);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 2);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
				}
				else
				{
					int boss_attack_damage = princess.Skill_Attack(dori_bear, true);

					control.gotoxy(x - 65, y + 3);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 2);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 1);
					std::cout << "공주가 " << princess.Get_Last_Attack_Name() << "를 시전했다!";
					Sleep(1500);

					if (boss_attack_damage == 0) {
						control.gotoxy(x - 65, y + 3);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 1);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 2);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 1);
						std::cout << "공주님의 공격력이 2 증가하였다!";
						Sleep(1500);
					}
					else {
						control.gotoxy(x - 65, y + 3);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 1);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 2);
						std::cout << "                                     ";
						control.gotoxy(x - 65, y + 1);
						std::cout << "도리베어는 " << boss_attack_damage << "의 피해를 입었다!";
						Sleep(1500);
					}
					hp_print();
				}
			}

			else if (x == 130 && y == 50) { // 가방 보기
				int check = player_bag.bag_open(dori_bear, princess);

				if (check == F_GRADE_CARD_END) {
					Sleep(1500);
					system("cls");
					end.show_SPEnd07();
					return true;
				}
				else if (check == INF_GAUNTLETS_END1) {
					Sleep(1500);
					system("cls");
					end.show_SPEnd10();
					return true;

				}
				else if (check == INF_GAUTTLETS_END2) {
					Sleep(1500);
					system("cls");
					end.show_SPEnd11();
					return true;
				}
				else if (check == EXIT || check == false) {
					control.gotoxy(115, 47);
					std::cout << "            ";
					control.gotoxy(115, 48);
					std::cout << "            ";
					control.gotoxy(115, 49);
					std::cout << "            ";
					control.gotoxy(115, 50);
					std::cout << "            ";
				}
				else {
					control.gotoxy(x - 65, y + 1);
					std::cout << "                                     ";
					control.gotoxy(x - 65, y + 2);
					std::cout << "                                     ";
					control.gotoxy(115, 47);
					std::cout << "            ";
					control.gotoxy(115, 48);
					std::cout << "            ";
					control.gotoxy(115, 49);
					std::cout << "            ";
					control.gotoxy(115, 50);
					std::cout << "            ";
					hp_print();
					boss_turn();
				}
				control.gotoxy(115, 47);
				std::cout << "   기본공격";
				control.gotoxy(115, 50);
				std::cout << "   특수공격";
				control.gotoxy(130, 47);
				std::cout << "   방어하기";
				control.gotoxy(130, 50);
				std::cout << "▶ 가방보기";
			}
		}
		}

		if (x == 115 && y == 47)
		{
			control.gotoxy(x - 50, y + 3);
			std::cout << "                                     ";
			control.gotoxy(x - 50, y + 1);
			std::cout << "                                     ";
			control.gotoxy(x - 50, y + 2);
			std::cout << "                                     ";
			control.gotoxy(x - 50, y + 1);
			std::cout << "공주에게 기본 공격을 가한다!";
		}
		else if (x == 130 && y == 47)
		{
			control.gotoxy(x - 65, y + 3);
			std::cout << "                                     ";
			control.gotoxy(x - 65, y + 1);
			std::cout << "                                     ";
			control.gotoxy(x - 65, y + 2);
			std::cout << "                                     ";
			control.gotoxy(x - 65, y + 1);
			std::cout << "공주가 주는 피해를 방어한다!";
		}
		else if (x == 115 && y == 50)
		{
			control.gotoxy(x - 50, y - 1);
			std::cout << "                                        ";
			control.gotoxy(x - 50, y);
			std::cout << "                                        ";
			control.gotoxy(x - 50, y + 1);
			std::cout << "                                        ";
			control.gotoxy(x - 50, y + 2);
			std::cout << "                                        ";
			control.gotoxy(x - 50, y - 2);
			std::cout << "공주에게 특수 피해를 가한다!      ";

			if (dori_bear.Get_Skill_Count() >= 1)
			{
				control.gotoxy(x - 50, y);
				std::cout << dori_bear.Get_Skill_Discription();
				std::cout << "(" << dori_bear.Get_Skill_Count() << "번)";
			}
			else
			{
				control.gotoxy(x - 50, y);
				std::cout << "사용 할 수 없어요.";
			}

		}
		else if (x == 130 && y == 50)
		{
			player_bag.bag_list_print();
		}

		if (princess.Get_HP() == 0)
		{
			Sleep(1500);
			system("cls");
			if (dori_bear.Get_Arms() == "Dori_Bear_arms")
			{
				end.show_SPEnd06();
				return true;
			}
			end.show_NorEnd09();
			return true;
		}
		if (dori_bear.Get_HP() == 0)
		{
			Sleep(3000);
			system("cls");
			if (dori_bear.Get_Passive() == DEADHARD)
			{
				end.show_SPEnd03();
				return true;
			}
			end.show_BadEnd02();
			return true;
		}
	}
}


void Game::test_setting() {
	
	using std::cout;
	using std::cin;
	using std::endl;

	while (1) {
		cout << "팔을 고르세요" << endl;
		cout << "1. 도리베어 팔 // 2. 날개 // 3. 나뭇가지 // 4. 고양이 팔 // 5. 인형 팔 // 6. 아이스크림 팔" << endl;
		cout << ">>";
		int arm_temp = 0;
		cin >> arm_temp;

		if (arm_temp > 6 || arm_temp < 1) {
			cout << "다시 입력" << endl;;
		}
		else {
			this->dori_bear.Set_Arms(arm_temp + 14);
			break;
		}
	}

	while (1) {
		cout << "패시브를 고르세요" << endl;
		cout << "1. 데드하드 // 2. 씨뿌리기 // 3. 경청하기" << endl;
		cout << ">>";
		int passive_temp = 0;
		cin >> passive_temp;

		if (passive_temp == 1) {
			this->dori_bear.Set_Passive(DEADHARD);
			break;
		}
		else if (passive_temp == 2) {
			this->dori_bear.Set_Passive(FARMING);
			break;
		}
		else if (passive_temp == 3) {
			this->dori_bear.Set_Passive(LISTEN);
			break;
		}
		else {
			cout << "다시 입력" << endl;
		}
	}

	int i = 0;
	int item_temp = 0;
	while (i < 3) {
		cout << "아이템을 고르세요 (최대 3번 // " << i << "지금 고른 횟수)" <<endl;
		cout << "1. 껌 (보호막 10 획득)" << endl;
		cout << "2. 솜 (체력 10 회복)" << endl;
		cout << "3. 없음 (없음)" << endl;
		cout << "4. 인싸토끼 (보스 공격력 2 감소)" << endl;
		cout << "5. 인피니티 건틀릿 (1/2확률로 상대 kill or 나 kill)" << endl;
		cout << "6. 매직서클 (보스에게 50의 데미지)" << endl;
		cout << "7. f맞은 성적표 (씨뿌리기 있는 상태로 쓰면 히든엔딩)" << endl;
		cout << ">>";
		cin >> item_temp;

		if (item_temp > 7 || item_temp < 1) {
			cout << "다시 입력" << endl;
		}
		else {
			this->player_bag.input_item(item_temp);
			i++;
		}

	}
}
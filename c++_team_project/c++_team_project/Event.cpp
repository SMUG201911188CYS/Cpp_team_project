#include "enum.h"

Event::Event() {
	rand_value = 0;
}

int Event::rand() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 9);

	return dist(gen);
}

int Event::pot() {
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "항아리 여는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "항아리 여는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "항아리 여는중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "항아리 여는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "항아리 여는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	rand_value = rand();
	
	if (pot_item_percent[rand_value] == COTTON)
	{
		std::cout << "솜뭉치를 얻었습니다.";
		Sleep(3000);
		return COTTON;

	}
	else if (pot_item_percent[rand_value] == CHEWING_GUM)
	{
		std::cout << "껌을 얻었습니다.";
		Sleep(3000);
		return CHEWING_GUM;

	}
	else
	{
		std::cout << "아무것도 나오지 않았습니다...";
		Sleep(3000);
		return NONE;
	}

}

int Event::box() {
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "상자 여는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "상자 여는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "상자 여는중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "상자 여는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "상자 여는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	rand_value = rand();

	if (box_item_percent[rand_value] == COTTON)
	{
		std::cout << "솜뭉치를 얻었습니다.";
		Sleep(3000);
		return COTTON;
	}
	else if (box_item_percent[rand_value] == CHEWING_GUM)
	{
		std::cout << "껌을 얻었습니다.";
		Sleep(3000);
		return CHEWING_GUM;

	}
	else if (box_item_percent[rand_value] == NONE)
	{
		std::cout << "아무 것도 나오지 않았습니다...";
		Sleep(3000);
		return NONE;
	}
	else if (box_item_percent[rand_value] == INSSA_RABBIT)
	{
		std::cout << "인싸토끼를 얻었습니다.";
		Sleep(3000);
		return INSSA_RABBIT;

	}
	else if (box_item_percent[rand_value] == INF_GAUNTLETS)
	{
		std::cout << "WoW !!!! 인피니티 건틀릿을 얻었습니다.";
		Sleep(3000);
		return INF_GAUNTLETS;
	}
	return NONE;
}

int Event::hole()
{
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "구덩이 파보는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "구덩이 파보는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "구덩이 파보는중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "구덩이 파보는중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "구덩이 파보는중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "낫띵 이스 해브.....☆";
	Sleep(3000);
	return NONE;
}

int Event::bookshelf()
{
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "책을 꺼내는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "책을 꺼내는 중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "책을 꺼내는 중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "책을 꺼내는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "책을 꺼내는 중..";
	Sleep(1000);
	rand_value = rand();

	if (book_item_percent[rand_value] == MATH) // 수학의 정석
	{
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "수학의 정석이라는 책이다.";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "보기만 해도 기분 나쁘니 그냥 가자.";
		Sleep(3000);
	}
	else if (book_item_percent[rand_value] == TAGD) // TAGD
	{
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "The Art Of Game Design 이라는 책이다..";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "라면 받침으로 좋을 것 같다.";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "이 하수구를 나가는 데 필요는 없을 것 같다.";
		Sleep(3000);
	}
	else if (book_item_percent[rand_value] == GET_FARMING) // 농사의 정석, C뿌리기 획득
	{
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "농사의 정석이라는 책이다.";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "'교수님의'C뿌리기에 대한 설명이 나와있다.";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "책을 읽고 C뿌리기를 배웠다!";
		Sleep(3000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "F맞은 성적표를 공주에게 사용하면 특별한 일이 일어날지도...?";
		Sleep(3000);

		return GET_FARMING;
	}

	return NONE;
}

int Event::mouse() {

	rand_value = rand();
	char a[] = "언젠가 쥐가 구멍을 빠져나와 치즈를 가져갈 것을 알기에,,";
	char b[] = "의지가 차오른다.";

	if (mouse_item_percent[rand_value] == NONE)
	{
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "그저 쥐구멍인가 보다.";
		Sleep(3000);
		return NONE;
	}

	else if (mouse_item_percent[rand_value] == GET_CHEESE)
	{
		system("cls");
		for (int i = 0; i < strlen(a); i++)
		{
			Control::gotoxy((i * 2) + 20, 25);
			std::cout << a[i];
			Sleep(200);
		}
		for (int i = 0; i < strlen(b); i++)
		{
			Control::gotoxy((i * 2) + 57, 27);
			std::cout << b[i];
			Sleep(200);
		}
		Control::gotoxy(65, 29);
		std::cout << "치즈를 먹어서 보호막 10을 얻었습니다.";
		Sleep(3000);

		return GET_CHEESE;
	}

	return NONE;
}

int Event::circle() {

	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "이상한 원 탐색중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "이상한 원 탐색중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "이상한 원 탐색중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "이상한 원 탐색중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "이상한 원 탐색중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	rand_value = rand();

	if (circle_item_percent[rand_value] == NONE)
	{
		std::cout << "아무일도.. 없었다..";
		Sleep(3000);
	}
	else if (circle_item_percent[rand_value] == MAGIC_CIRCLE)
	{
		std::cout << "아니 이것은....?";
		Sleep(1000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "Magic Circle을 획득하였습니다!!";
		Sleep(3000);
		return MAGIC_CIRCLE;
	}

	return NONE;
}

int Event::button() {
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "스위치를.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "스위치를 눌.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "스위치를 눌러.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "스위치를 눌러보.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "스위치를 눌러보자..";
	Sleep(1000);
	rand_value = rand();


	if (button_tiem_percent[rand_value] == NONE)
	{
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "눌러봐도 아무 일도 없었다.";
		Sleep(3000);
	}
	else if (button_tiem_percent[rand_value] == GET_DEADHARD)
	{
		system("cls");
		Control::gotoxy(2, 2);
		std::cout << "(쿠궁...)";
		Sleep(1000);
		system("cls");
		Control::gotoxy(20, 10);
		std::cout << "(쿠궁......)";
		Sleep(1000);
		system("cls");
		Control::gotoxy(40, 20);
		std::cout << "(콰광.........)";
		Sleep(2000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "어디서 물소리가 들리는데...?";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "(쿠곽ㄱ가ㅘㅗ아ㅗ가과왕아)";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "으으으ㅔㅇ에ㅔㄱ!!!! 도 망 쳐 !!!!!!!!!!!!!";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "도리베어는 죽기살기로 통로를 탈출했다!";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "도리베어는 죽기살기를 얻었다!!!";
		Sleep(3000);
		system("cls");

		return GET_DEADHARD;
	}
	return NONE;
}

int Event::paper() {
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "종이조각 맞춰보는 중.";
	Sleep(1000);
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "종이조각 맞춰보는 중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "종이조각 맞춰보는 중...";
	Sleep(1000);
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "종이조각 맞춰보는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "종이조각 맞춰보는 중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	rand_value = rand();

	if (paper_item_percent[rand_value] == NONE)
	{
		std::cout << "맞춰보니.. 청구서였다고한다..";
		Sleep(3000);
		return NONE;
	}
	else if (paper_item_percent[rand_value] == F_GRADE_CARD)
	{
		std::cout << "어라....? F맞은 성적표인가...?";
		Sleep(1000);
		system("cls");
		Control::gotoxy(65, 25);
		std::cout << "F 맞은 성적표를 얻었습니다.";
		Sleep(3000);
		return F_GRADE_CARD;
	}

	return NONE;
}

int Event::npc(int sewer_in)
{
	system("cls");
	rand_value = rand();
	
	if (npc_item_percent[rand_value] == MEET_IC) // 아이스크림 상인
	{
		Control::gotoxy(55, 25);
		std::cout << "아이스크림 사세요!!! 단 돈 20골드!!!";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "돈이 없다고요??? 그럼 그냥 드릴게요!!!";
		Sleep(3000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "아이스크림을 얻었습니다!!! 야호!!!";
		Sleep(3000);
		return MEET_IC;
	}
	else if (npc_item_percent[rand_value] == MEET_HOMELESS) // 노숙자
	{
		if (sewer_in == 1) {
			system("cls");
			Control::gotoxy(55, 25);
			std::cout << "??? : 으윽....";
			Sleep(3000);
			system("cls");
			Control::gotoxy(55, 25);
			std::cout << "이상한 사람인 것 같다.";
			Sleep(3000);
			Control::gotoxy(55, 30);
			std::cout << "▶ 말을 건다";
			Control::gotoxy(55, 31);
			std::cout << "   기분 나쁘니 그냥 가자";
			int x = 55;
			int y = 30;
			while (1) {
				int n = Control::key_control();
				switch (n) {
				case UP: {
					if (y > 30) {
						Control::gotoxy(x, y);
						std::cout << "   ";
						Control::gotoxy(x, --y);
						std::cout << "▶";
					}
					break;
				}
				case DOWN: {
					if (y < 31) {
						Control::gotoxy(x, y);
						std::cout << "   ";
						Control::gotoxy(x, ++y);
						std::cout << "▶";
					}
					break;
				}
				case SUBMIT: {
					if (y == 30) {
						system("cls");
						Control::gotoxy(55, 25);
						std::cout << "??? : 으,,어어,,,어";
						Sleep(3000);
						Control::gotoxy(55, 30);
						std::cout << "▶ 말을 계속 걸어본다";
						Control::gotoxy(55, 31);
						std::cout << "   어딘가 모자른 사람 같다. 그냥 가자";
						x = 55, y = 30;
						while (1) {
							switch (n) {
							case UP: {
								if (y > 30) {
									Control::gotoxy(x, y);
									std::cout << "   ";
									Control::gotoxy(x, --y);
									std::cout << "▶";
								}
								break;
							}
							case DOWN: {
								if (y < 31) {
									Control::gotoxy(x, y);
									std::cout << "   ";
									Control::gotoxy(x, ++y);
									std::cout << "▶";
								}
								break;
							}
							case SUBMIT: {
								if (y == 30) {
									system("cls");
									Control::gotoxy(55, 25);
									std::cout << "??? : 공주가,, 화가 나있어,,";
									Sleep(3000);
									Control::gotoxy(55, 30);
									std::cout << "▶ 무슨 일인지 자세히 물어보자";
									x = 55, y = 30;
									while (1) {
										int n = Control::key_control();
										switch (n) {
										case SUBMIT: {
											if (y == 30) {
												system("cls");
												Control::gotoxy(55, 25);
												std::cout << "??? : 공주님이 무슨 일인지 화가 잔뜩 나있어..";
												Sleep(3000);
												Control::gotoxy(55, 27);
												std::cout << "      화를 주체하지 못하고 지하실에서 울분을 토하고 있지...";
												Sleep(3000);
												Control::gotoxy(55, 29);
												std::cout << "도리베어 : 어떻게 하면 진정시키죠?";
												Sleep(3000);
												system("cls");
												Control::gotoxy(55, 25);
												std::cout << "??? : 나의 사부님이 항상 말하셨지...";
												Sleep(3000);
												Control::gotoxy(55, 27);
												std::cout << "      안생에서 가장 중요한 것은 '경청하기'라고...";
												Sleep(3000);
												Control::gotoxy(55, 29);
												std::cout << "      그녀를 공격하지 말고 귀를 기울여줘....";
												Sleep(3000);
												Control::gotoxy(55, 31);
												std::cout << "	  '방어하기'를 하다 보면 괜찮아질지도.....";
												Sleep(3000);
												system("cls");
												Control::gotoxy(55, 25);
												std::cout << "경청하기를 배웠다.";
												Sleep(3000);
												return GET_LISTEN;
											}
										}
										}
									}
								}
								else { return NONE; }
							}
							}

						}
					}
					else { return NONE; }
				}
				}
			}
		}
		else {
			Control::gotoxy(65, 25);
			std::cout << "자고 있는 노숙자다.";
			return NONE;
		}
	}
	return NONE;
}


int Event::pipe(int sewer_in) // 오브젝트 목록 : 파이프
{
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "파이프 안을 뒤져보는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "파이프 안을 뒤져보는 중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "파이프 안을 뒤져보는 중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "파이프 안을 뒤져보는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "파이프 안을 뒤져보는 중..";
	Sleep(1000);
	system("cls");

	if (sewer_in == 1) // c많은 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "파이프 안에서 앵무새 날개를 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "앵무새 날개를 도리베어의 팔에 부착하였다!!";
		Sleep(3000);
		return GET_Wings;
	}

	else if (sewer_in == 2) // G417 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "파이프 안에서 고양이 팔을 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "고양이 팔을 내 팔에 부착하였다!!";
		Sleep(3000);
		return GET_CatArms;
	}

	else if (sewer_in == 3) // 평범한 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "파이프 안에서 도리베어의 팔을 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "(띠요옹?!?! 이것은 내 팔이잖어?!?!)";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "도리베어의 팔을 부착하였다!";
		Sleep(3000);
		return GET_DoriArms;
	}

	return NONE;
}

int Event::lake(int sewer_in) // 오브젝트 목록 : 고인 물
{
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "고인물 안을 뒤져보는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "고인물 안을 뒤져보는 중..";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "고인물 안을 뒤져보는 중...";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "고인물 안을 뒤져보는 중.";
	Sleep(1000);
	system("cls");
	Control::gotoxy(65, 25);
	std::cout << "고인물 안을 뒤져보는 중..";
	Sleep(1000);
	system("cls");

	if (sewer_in == 1) // c많은 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "고인 물 안에서 나뭇가지를 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "나뭇가지를 도리베어의 팔에 부착하였다!!";
		Sleep(3000);
		return GET_Twigs;
	}

	else if (sewer_in == 2) // G417 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "고인 물 안에서 바비인형의 팔을 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "바비인형의 팔을 내 팔에 부착하였다!!";
		Sleep(3000);
		return GET_BarbieArms;
	}

	else if (sewer_in == 3) // 평범한 하수구
	{
		Control::gotoxy(55, 25);
		std::cout << "고인 물 안에서 아이스크림 팔을 발견했다!!";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "(띠요옹..? 고인 물 안에 아이스크림이..?)";
		Sleep(1000);
		system("cls");
		Control::gotoxy(55, 25);
		std::cout << "아이스크림 팔을 부착하였다!";
		Sleep(3000);
		return GET_BarbieArms;
	}

	return NONE;
}
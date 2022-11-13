#include "enum.h"

Room::Room() {
	this->sewer_in = 0;
	this->cross_in[0] = 0;
	this->cross_in[1] = 0;
	this->cross_in[2] = 0;
	this->x = 36;
	this->y = 24;
}

bool Room::intro() {
	control.gotoxy(36, START);
	std::cout << "▶";
	control.gotoxy(36, y + EXIT);
	std::cout << "   ";

	while (1)
	{
		int n = control.key_control();
		switch (n)
		{
		case UP:
		{
			if (y > START)
			{
				control.gotoxy(36, EXIT);
				std::cout << "   ";
				y += -7;
				control.gotoxy(36, START);
				std::cout << "▶";
			}
			break;
		}
		case DOWN:
		{
			if (y < EXIT)
			{
				control.gotoxy(36, START);
				std::cout << "   ";
				y += 7;
				control.gotoxy(36, EXIT);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT:
		{
			if (y == START) return true;
			else return false;
		}
		}
	}
}

bool Room::sewer() {
	x = 0;
	y = 50;
	control.gotoxy(x, L);
	std::cout << "▶ 왼쪽 하수구";
	control.gotoxy(x, M);
	std::cout << "   가운데 하수구";
	control.gotoxy(x, R);
	std::cout << "   오른쪽 하수구";
	while (sewer_in == 0) {
		int n = control.key_control();
		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 어떤 하수구를 선택했는지 멤버에 넣음
				this->sewer_in = 1;
			}
			else if (y == 51) {
				this->sewer_in = 2;
			}
			else if (y == 52) {
				this->sewer_in = 3;
			}
			return true;
		}
		}
	}
	return true;
}

bool Room::crossroad() {

	x = 0, y = 50;
	control.gotoxy(x, y);
	std::cout << "▶ 왼쪽 길";
	control.gotoxy(x, y + 1);
	std::cout << "   가운데 길";
	control.gotoxy(x, y + 2);
	std::cout << "   오른쪽 길";
	while (1) {
		int n = control.key_control();
		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				if (cross_in[0] == 0) {
					cross_in[0] = 1;
				}
				else if (cross_in[1] == 0) {
					cross_in[1] = 1;
				}
				else if (cross_in[2] == 0) {
					cross_in[2] = 1;
				}
				return true;
			}
			else if (y == M) {
				if (cross_in[0] == 0) {
					cross_in[0] = 2;
				}
				else if (cross_in[1] == 0) {
					cross_in[1] = 2;
				}
				else if (cross_in[2] == 0) {
					cross_in[2] = 2;
				}
				return true;
			}
			else if (y == R) {
				if (cross_in[0] == 0) {
					cross_in[0] = 3;
				}
				else if (cross_in[1] == 0) {
					cross_in[1] = 3;
				}
				else if (cross_in[2] == 0) {
					cross_in[2] = 3;
				}
				return true;
			}
		}
		}
	}

}

int Room::c_room1_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 항아리";
	control.gotoxy(0, M);
	std::cout << "   상자";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return pot;
			}
			else if (y == M) {
				return box;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::c_room1_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 종이조각";
	control.gotoxy(0, M);
	std::cout << "   항아리";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return paper;
			}
			else if (y == M) {
				return pot;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}


int Room::c_room1_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 종이조각";
	control.gotoxy(0, M);
	std::cout << "   상자";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return paper;
			}
			else if (y == M) {
				return box;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::c_room2_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 책장";
	control.gotoxy(0, M);
	std::cout << "   이상한 사람";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "책장에서는 농사의 정석, 수학의 정석, The art of game design을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return bookshelf;
			}
			else if (y == M) {
				return npc;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "책장에서는 농사의 정석, 수학의 정석, The art of game design을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::c_room2_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 상자";
	control.gotoxy(0, M);
	std::cout << "   책장";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return box;
			}
			else if (y == M) {
				return bookshelf;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "책장에서는 농사의 정석, 수학의 정석, The art of game design을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::c_room2_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "구덩이는 무엇일까요?";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case SUBMIT: {
			if (y == L) {
				return hole;
			}
		}
		}
	}
}

int Room::c_room3_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 파이프";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return pipe;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::c_room3_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 고인물";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return lake;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::c_room3_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 종이조각";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return paper;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

// normal room

int Room::n_room1_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 종이조각";
	control.gotoxy(0, M);
	std::cout << "   상자";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return paper;
			}
			else if (y == M) {
				return box;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::n_room1_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 쥐구멍";
	control.gotoxy(0, M);
	std::cout << "   항아리";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "치즈가 보입니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return mouse;
			}
			else if (y == M) {
				return pot;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}


int Room::n_room1_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 상자";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return box;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::n_room2_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 스위치";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   이상한 사람";
	control.gotoxy(x + 15, L);
	std::cout << "스위치를 누르면 어떤 일이 발생할 수도 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return button;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return npc;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "스위치를 누르면 어떤 일이 발생할 수도 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";
		}
	}
}

int Room::n_room2_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 상자";
	control.gotoxy(0, M);
	std::cout << "   스위치";
	control.gotoxy(0, R);
	std::cout << "   종이조각";
	control.gotoxy(x + 15, L);
	std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return box;
			}
			else if (y == M) {
				return button;
			}
			else if (y == R) {
				return paper;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "스위치를 누르면 어떤 일이 발생할 수도 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
	}
}

int Room::n_room2_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "구덩이는 무엇일까요?";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case SUBMIT: {
			if (y == L) {
				return hole;
			}
		}
		}
	}
}

int Room::n_room3_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 파이프";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   상자";
	control.gotoxy(x + 15, L);
	std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return pipe;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return box;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::n_room3_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 고인물";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return lake;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::n_room3_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 쥐구멍";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "치즈가 보입니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return mouse;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

// g417 room


int Room::g_room1_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 상자";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   종이조각";
	control.gotoxy(x + 15, L);
	std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return box;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return paper;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
	}
}

int Room::g_room1_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 쥐구멍";
	control.gotoxy(0, M);
	std::cout << "   항아리";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "치즈가 보입니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return mouse;
			}
			else if (y == M) {
				return pot;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, M);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}


int Room::g_room1_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "구덩이는 무엇일까요?";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case SUBMIT: {
			if (y == L) {
				return hole;
			}
		}
		}
	}
}

int Room::g_room2_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 이상한 원";
	control.gotoxy(0, M);
	std::cout << "   상자";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "이상한 원에선 Magic Circle을 획득할 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return circle;
			}
			else if (y == M) {
				return box;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "이상한 원에선 Magic Circle을 획득할 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::g_room2_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 이상한 사람";
	control.gotoxy(0, M);
	std::cout << "   항아리";
	control.gotoxy(0, R);
	std::cout << "   상자";
	control.gotoxy(x + 15, L);
	std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return npc;
			}
			else if (y == M) {
				return pot;
			}
			else if (y == R) {
				return box;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::g_room2_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 이상한 사람";
	control.gotoxy(0, M);
	std::cout << "   이상한 원";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return npc;
			}
			else if (y == M) {
				return circle;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "정체를 알 수 없습니다. 특정 이벤트를 겪을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "이상한 원에선 Magic Circle을 획득할 수 있습니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::g_room3_1() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 파이프";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   구덩이";
	control.gotoxy(x + 15, L);
	std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return pipe;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return hole;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "파이프에서는 도리베어의 팔을 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "구덩이는 무엇일까요?";
		}
	}
}

int Room::g_room3_2() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 고인물";
	control.gotoxy(0, M);
	std::cout << "   쥐구멍";
	control.gotoxy(0, R);
	std::cout << "   상자";
	control.gotoxy(x + 15, L);
	std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return lake;
			}
			else if (y == M) {
				return mouse;
			}
			else if (y == R) {
				return box;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "고인물 안을 뒤지면 무언가 나올 것 같습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "치즈가 보입니다.";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "상자에서는 껌, 솜뭉치, 인싸토끼, 인피니티 건틀릿, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::g_room3_3() {
	x = 0, y = 50;

	control.gotoxy(0, L);
	std::cout << "▶ 종이조각";
	control.gotoxy(0, M);
	std::cout << "   구덩이";
	control.gotoxy(0, R);
	std::cout << "   항아리";
	control.gotoxy(x + 15, L);
	std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";

	while (1) {
		int n = control.key_control();

		switch (n) {
		case UP: {
			if (y > L) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, --y);
				std::cout << "▶";
			}
			break;
		}
		case DOWN: {
			if (y < R) {
				control.gotoxy(x, y);
				std::cout << "   ";
				control.gotoxy(x, ++y);
				std::cout << "▶";
			}
			break;
		}
		case SUBMIT: {
			if (y == L) {
				return paper;
			}
			else if (y == M) {
				return hole;
			}
			else if (y == R) {
				return pot;
			}
		}
		}
		if (y == L)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "종이조각에서는 F맞은 성적표,청구서를 얻을 수 있습니다.";
		}
		else if (y == M)
		{
			control.gotoxy(x + 15, R);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, L);
			std::cout << "                                                                                 ";
			control.gotoxy(x + 15, M);
			std::cout << "구덩이는 무엇일까요?";
		}
		else if (y == R)
		{
			control.gotoxy(x + 15, M);
			std::cout << "                                                                              ";
			control.gotoxy(x + 15, R);
			std::cout << "항아리에서는 껌, 솜뭉치, 꽝을 얻을 수 있습니다.";
		}
	}
}

int Room::Get_Crossroad_In(int index) {
	return cross_in[index];
}

int Room::Get_Sewer_in() {
	return sewer_in;
}
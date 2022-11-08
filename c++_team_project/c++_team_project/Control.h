#ifndef __Control_h__
#define __Control_h__

class Control {
private:
	int x;
	int y;
public:
	enum {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SUBMIT
	};
	Control();
	void delete_blink(); // 키보드 깜박이는거 없애기
	void gotoxy(int x, int y); // 이동하기
	int key_control(); // 입력하는 키 리턴하기
};


#endif // !__Control_h__

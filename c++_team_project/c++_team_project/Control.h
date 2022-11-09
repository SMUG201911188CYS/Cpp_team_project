#ifndef __CONTROL_H__
#define __CONTROL_H__

class Control {
private:
	int x;
	int y;
public:
	Control();
	void delete_blink(); // 키보드 깜박이는거 없애기
	void gotoxy(int x, int y); // 이동하기
	int key_control(); // 입력하는 키 리턴하기
};


#endif // !__Control_h__

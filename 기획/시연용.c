#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include<Windows.h>
#include<mmsystem.h>

#pragma comment(lib, "Winmm.lib")

#define SANSBGM "C:\\Users\\money\\source\\repos\\도리베어\\BGM.wav"
#define OPENBGM "C:\\Users\\money\\source\\repos\\도리베어\\OPBGM.wav"
#define RESULTBGM "C:\\Users\\money\\source\\repos\\도리베어\\REBGM.wav"
#define BOSSSTARTBGM "C:\\Users\\money\\source\\repos\\도리베어\\BSBGM.wav"





#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

void notcon() // 키보드 깜빡이는거 없애기
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

typedef enum _Passive { // 패시브 나열
	DeadHard = 311, DropC = 312, Listen = 313
};
typedef enum _Arms { // 팔 나열
	DoriArms = 411, Wings = 412, Twigs = 413, CatArms = 414, BarbieArms = 415, ICArms = 416
};
typedef struct _PlayerBag {
	int arms;
	int items[100];
	int passive;
}Bag;

int cheese = 0;
char bossListen[8][300] = { "공주 : %&^$#%@!!# %!!!!!!","도리베어: (방어하기를 계속 해보자.)","공주 : $#^%$&*%^$^#" ,"도리베어: (방어하기를 계속 해보자.)","공주 : ㅆ>>>ㅡㅡㅢㅣ>>>>", "도리베어: (조금 진정된 것 같다),","공주 : 으>>>>>으으ㅡㅡㅇ>>>","도리베어: (흠..조금 더 기다려보자)" };
int whatlisten = 0;
char haveitem[3][100] = { "","","" };
char itemeffect[3][100] = { "","","" };
int whatitemuse[3][1];
int whodie[2] = { 0,1 }; // 0 = 공주 , 1 = 플레이어
int potitems[10] = { 0,0,0,0,1,1,1,1,2,2 }; // 껌 = 0, 솜 = 1, 꽝 =2
int boxitems[10] = { 0,0,1,1,2,2,3,3,3,4 }; // 껌 = 0, 솜 = 1, 꽝 = 2, 인싸토끼 =3, 인피니티 건틀릿 = 4
int circleitems[10] = { 2, 2, 2, 2, 5, 5, 5, 5, 5, 5 }; // 꽝 = 2, Magic Circle = 5
int paperitems[10] = { 2, 2, 2, 2, 6, 6, 6, 6, 6, 6 }; // 꽝 = 2, F맞은 성적표 = 6
int buttonitems[10] = { 2, 2, 2, 2, 2, 2, 7, 7, 7, 7 }; // 꽝 = 2, 죽기살기 획득 = 7
int mouseitems[10] = { 2, 2, 2, 2, 2, 2, 8, 8, 8, 8 }; //꽝 = 2, 의지가 차오름 = 8
int bookitems[10] = { 9, 9, 9, 10, 10, 10, 11, 11, 11, 11 }; // 수학의 정석 = 9, TAGD = 10, 농사의 정석 = 11
int npcitems[10] = { 12, 12, 12, 12, 12, 12, 13, 13, 13, 13 }; // 아이스크림 상인 : 12, 노숙자 : 13
int buttongo[3] = { 14, 15, 16 }; // C1 이동 : 14, C2 이동 : 15, C3 이동 : 16
int bossattack[10] = { 17,17,17,18,18,18,18,19,19 ,20 }; // 17 = 손목 , 18 = 육두, 19 = 침, 20 = 술주정
int bosspower = 0;
int x, y;
int room = 0;
int roomin = 0;
int whatitem = 0;
int whatattack = 0;
int whatdamage = 0;
int k = 1; // while 무한루프를 탈출하기 위해 오브젝트 누르면 탈출
int muham = 1;
int wingsCount = 3;
int icCount = 1;
int catCount = 3;
Bag Player = { 0, 0 };


void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸드 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keycontrol()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{
		return SUBMIT;
	}

}

void textcolor(int color_number) // 텍스트 칼라 변경

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void startintro()
{
	printf("\n");
	printf("                 ,i200a;                                                                       .:MMMMMM;:                                             \n");
	printf("                 ,2MMMMMMi                    i8MSi                                            ,,MM   MM:,                                            \n");
	printf("                 .MM   ;MM:  ,SWMBX.  ;SXWM8;,:XM7;                                            ,iMB:XXM@.  :0MMMM7,  .SWWa;, .rXS@MZ;,                \n");
	printf("                 .MM    ZM; .MM@BMMB. iMMMMM7; Z0.                                             ,;MMMMMMS . WMZ  MM.;,MMB8MMi..XMM@MM7;                \n");
	printf("                 :M@    MM, ,MM   MM. iMMi     MM,                                             ,7MX   ZMrr.MMM@WZS:i2M7  MM8 ..MM                     \n");
	printf("                 iMM8WMMM.  ,ZMMWMMZ, iMM;     MMi                                             :7M8   @Mr:.aMM      ;MMMMaMM,; MM.                    \n");
	printf("                .;ZBMMai     .;8BZ;.  i20;.   iaMr:                                            :;MMMMMMS,  .r0MMMX: .:Sai 7W;:,aZi                    \n");
	printf("                                                                    .,,..                                                                             \n");
	printf("                                                           i7a0W@MMMMMMMMMM@W0ZXi.                                                                    \n");
	printf("                                                      .rZWMMMW82Xrii:,,,:i;7SZB@MM@ZX,                                                                \n");
	printf("                                                   .XBMMWa;,                    .;2WMM@a:                                                             \n");
	printf("                                                 rBMM8r.                             ;ZMMWX                                                           \n");
	printf("                                               S@MB7                                    ;0MMa,                                                        \n");
	printf("                                             XMM8i                                        ,ZMMa.                                                      \n");
	printf("                                           ;BMBi                                            .ZMMX                                                     \n");
	printf("                                          aMMX                                                iWM0.                                                   \n");
	printf("                                        .BM0,                                                    aM@i                                                 \n");
	printf("                                      ,WMa                                                        XM@7                                                \n");
	printf("                                     ,@MS                                                          ;@@7                                               \n");
	printf("                                     WM2                                                             r@@;                                             \n");
	printf("                                    W@7                                                              ,W@;                                             \n");
	printf("                                   BWX                                                                iWW,                                            \n");
	printf("                                  :WW:");
	textcolor(14);
	printf("                      PRESS ANY KEY TO START");
	textcolor(15);
	printf("                     BWX\n");
	printf("                                  rWB                                                                  ZWa                                            \n");
	printf("                                  XW0                                                                  aW8                                            \n");
	printf("                                  2W8                                                                  aW8                                            \n");
	printf("                                  XWB                         .rr;::ii,i;7X.                           ZBZ                                            \n");
	printf("                                  ;WW                        ia. 8i:::iZX  Z,                          0WS                                            \n");
	printf("                                   WWr                       Z  X:      i2 :2                         .BW;                                            \n");
	printf("                                   ZWZ                       Si a         8S,                         XWB                                             \n");
	printf("                                   ;@W,                       ;B.         .a                          BW2                                             \n");
	printf("                                    0@Z                       .2   -   -   2.                        SWW                                              \n");
	printf("                                    ,@@r                      2,     ▽    Z.                       ,WW7                                              \n");
	printf("                                     X@@:                     iX          7:                        BWZ                                               \n");
	printf("                                      aMW. ..,,,,,:,,:::,::,,,.X8rii:ii;XZr.:iiiiiiiiiiii;;;;;;;i,.8W0                                                \n");
	printf("                                       ZMW8X2aZZZZZZZZaaZaaaaa2X2aMr...  0SS22222222222222222SSXr2W@0                                                 \n");
	printf("                                        2MB:                     .7      :;                      Z@8                                                  \n");
	printf("                                         r@M2                    2.       Z                    X@M2                                                   \n");
	printf("                                          .0MW;                  Z        X;                 i0MW;                                                    \n");
	printf("                                            7@M0i                8        X;               ,ZMM2                                                      \n");
	printf("                                              SMMBr              ,2S;X;X;2a              i8MMa.                                                       \n");
	printf("                                                XWMMa:            X, Z a  2           ,SWM@2.                                                         \n");
	printf("                                                  iZMMMZr.        X  X X  X.      .;aWMM8r                                                            \n");
	printf("                                                     iaWMM@0Sr:.  2.,X 7  X  ,;XZWMMWZr                                                               \n");
	printf("                                                        .;2BMMMMMWMMM@ZMMMMWMMM@0ar,                                                                  \n");
	printf("                                                              :i7XXXXaZ2SXX7;:.                                                                       \n");

	_getch(); // 아무키나 누르면 다음 코드로 넘어가는것
	system("cls"); // 화면 클리어

	return;
}

void mainintro()
{
	printf("                                                                   \n          ::BBQBBBi..                      :iv::        . BBs:7RBB.:\n          .sBP iJBB1.     ...     .  ..   ..BB2:        . BB    BB.:  .:qBBj..     ..      .  ... .\n         . QB:    BB....UBBBBBi..:vBBBBBK.: .i :        . BBEBBBQv   .2BBUPBB.. .rBBBBQr. :iBQBBBB::\n         . BB .   gBr:.UBQ::rBB:: vBBrrDI.i BB..        : BBvKDBBR ..iBBr:5BBi:.7BB: QBB . .BQU:PS:.\n    =====. BB    :BB r EBY   QB7 . BB .   ..BB .        ..QB    uBK.:7BBBg5r:.i QB: :BBB: . BB   ::================================================\n    =====:.BBgDBBBBr. ..BBBQBBD. . BB..   :.BB..        :.BQ    BB7.: BBBrir:: .iQBBBEjQB r BQi. ..================================================\n    ||   .:IbBBBMs..   ..7dQXi . .:Pb:.   .:bB::        ..QBBBQBB1.. ..vRBBBZ:  .:Y2i  gP::.sM::                                                 ||\n    ||                                        .          ..:7JJi.            .                                                                   ||\n    ||                                                                                                                                           ||\n    ||                                                                                                                                           ||\n    ||                                                                                                                                           ||\n");
	printf("    ||                                                                                                                                           ||\n");
	printf("    ||                                                                                                           .rr    .     .                  ||\n");
	printf("    ||                                                                                                            LvBJvr7JUiIj.7s                ||\n");
	printf("    ||                                                                                                          2::s.      .1I: M                ||\n");
	printf("    ||                                                                                                          7Qi     .     :QL                ||\n");
	printf("    ||                                                                                                        sI:              :U                ||\n");
	printf("    ||                                                                                                      JX:    --    --    .d                ||\n");
	printf("    ||                                                                                                    .g:                  vJ                ||\n");
	printf("    ||                                                                                                    P:        ▽        .R                 ||\n");
	printf("    ||                                                                                                    v1                  b                  ||\n");
	printf("    ||                                                                                                     51.             .KQ:                  ||\n");
	printf("    ||                                                                                                      :jjvi:.....::7Ur7I:s                 ||\n");
	printf("    ||                                       게       임       시       작                                      .:BQ::iii.   P 2:                ||\n");
	printf("    ||                                                                                                           u.U         :1 R                ||\n");
	printf("    ||                                                                                                          .s.s          M iU               ||\n");
	printf("    ||                                                                                                          b K           P. Q               ||\n");
	printf("    ||                                                                                                         :1.S           rs rI              ||\n");
	printf("    ||                                                                                                         g b            .d  M.             ||\n");
	printf("    ||                                                                                                        Ji S            .P  .M             ||\n");
	printf("    ||                                       게       임       종       료                                   .Z iv            :S   7J            ||\n");
	printf("    ||                                                                                                       Z  rr            P     Z            ||\n");
	printf("    ||                                                                                                      Q   .j           XQrKgq2B            ||\n");
	printf("    ||                                                                                                      XBBQBB7..    .iLsLvLBBB57            ||\n");
	printf("    ||                                                                                                        :i::K:ivQriB.   E                  ||\n");
	printf("    ||                                                                                                           .Y   g  P    Y7                 ||\n");
	printf("    ||                                                                                                           iu   d  D     g                 ||\n");
	printf("    ||                                                                                                           i2   D  E     g                 ||\n");
	printf("    ||                                                                                                           Q    Z  g     g                 ||\n");
	printf("    ||                                                                                                          :P   :S  g    .Z                 ||\n");
	printf("    ||                                                                                                          q.   sr :U    7s                 ||\n");
	printf("    ||                                                                                                         .D    g  5riPDgB                  ||\n");
	printf("    ||                                                                                                         .BBBBBj  .ZBBBS                   ||\n");
	printf("    ||                                                                                                           .::                             ||\n");
	printf("    ||                                                                                                                                           ||\n");
	printf("    ===============================================================================================================================================\n");
	printf("    ===============================================================================================================================================\n");

}

int mainchoice()
{
	int y = 24;
	gotoxy(36, y);
	printf("▶");
	gotoxy(36, y + 7);
	printf("   ");

	while (1)
	{
		int n = keycontrol();
		switch (n)
		{
		case UP:
		{
			if (y > 24)
			{
				gotoxy(36, y);
				printf("   ");
				y += -7;
				gotoxy(36, y);
				printf("▶");
			}
			break;
		}
		case DOWN:
		{
			if (y < 31)
			{
				gotoxy(36, y);
				printf("   ");
				y += 7;
				gotoxy(36, y);
				printf("▶");
			}
			break;
		}
		case SUBMIT:
		{
			return y;
		}
		}
	}

}

void sna()
{
	char a[] = { "                                   s.                           5                                             2   :r  S                              P                                    ;                            r                                             i   ,:  s                              P                                    :r                            s;.                                          2   ;;  S                              P                                     :r:..                         ,;;r.                                       X   ;;  5                              P                                       .,,S:                          5                                        2   ;;  S                              P                                          s                           s                                        2   r:  5                              P                                          2                           i                                        5   ;:  5                              P                                          .r;:.....:,                 S3.       ;S                  ,5;.       5   r:  2                              P                                             .,,:,:.rr.     ,;r;;.. .r: ;r:,,.,r;,i.     ,rr;,,...:r; .;;;;;;:.i   r:  S                              P                                                                                                              .i   s,  S                              P                                      ,,                                                                      .i   i.  2                              P                                      2s:                                                                     ,s   i.  5                              P                                     s. r;                                                                    ,s   S   2                              P                      :.            ,r   r:            :                                                      :r   i   S                              P                     .S,;;.         i     S           ;9,                                                     :r   5   5                              P                      s   ;r.      :;     .s        .s .r                                                     :;   S   S                              P                      i    .rr.    S   :;  i.      :s  .r                                                     :;   5   5                              P                      i      .r;  ;,   ;:  .i     r;    i                                                     ;;   S   5                              P                      i        ,r:s    ;:   i.   i,     i                                                     ;;   2   2                              P                      i   .;     ss    ;:   .r ,s       5                                                     r:   5   5                              P                      r,   i.    ;,    ;:    i:r     s. i                                                     ;:   2   5                              P                      ,;    i    s     ::    s2      s  i                                                     r:   5   S                              P                       S    s.  .r     ;:    :;      i  s.                                                    r:   2   5                              P                       i    .s  .r     ;:     S     .r  r,                                                Z   s,   2   5                              P                       ;;    S. .r     ;:     s.    ,;  ;:                                              Z     r,   2   2                              P                        5    .; ,;     :;     :;    r,  r,                          ,:;:;::.,,;:      Z       i.   5   2                              P                        ::      .r     ,i      S    i   r.                     r::Sr:.   .,rX; ,i   Z         i.   2   2                              P                        .2       s      ;      S   ,;   s.                    i. ;:          :i  i            S.   5   5                              P                     :;:;;r      s             2        5;2:                  r,;.             i.i            i.   2   2                              P                     i  .,S;;:::,5,,,.,..      ,  ..,,:si,:,;                  r5               H             5    S   5                              P                     i         ....,,,,::;:;;;:::;::,,.     i.                 .;               r.            S    5   2                              P                     i                                      ;:                 ,r    -    -     ,r            2   .i   2                              P                     s,                                     :;                 r,      ㅅ        i            5   .S   X                              P                      :5::;:;;;:;:;:;;;;;:;;;;;;;:;;;::.... r,                 S                r;            2   .i   5                              P                       i                             ..,,.X;,                  s,              ;s             2   .i   2                              P                       s                                  i                     2.         .;i5.              X   .s   5                              P                       ;:                                :;                      r:. ..,:;;:,S.;              2   ,s   2                              P                        S                                s.                       ,#i,,..    s ;:             2   ,r   2                              P                        i                                S                       ,:s         ;: 5             2   ,r   X                              P;::::,,..               ,;                              ;:                     .r,:;          5  S            2   :r   2                              P ..,,::;:;;;;;;;;;::,,.. X                              i                    :r: ;;           ;:  S.          5   :r   X                              P                  ..,,:,:2:                            .r                  :r, ,r.            .r   i,         5   :r   2                              P                          i                            5,                 ;   ;;               3    s;        S   :;   2                              P::;;;;;;;::::,,..         s                            2,:;;;;;;;:;::,,..,HS5rr                @     ;;       5   ;;   2                              P            ..,,:::;;;;;;:iHr:,                    ..:r;           ..,,:,,s@@@               .i,;     :      .i   ;;   X                              P;;;;;;;::,,..                .;:;;;:;;rrrr23X22iirr;:.                       ;;            .rr;r;@@@@@@;...  .5   ;;   2                              P       ..,,::::;;;;;;;::,,..                     ..,,::;;;;;;;:....      .:;:.;;.        :Ar   2   ,s95.,::;:rS;;;X:   X                              P                      ..,.:,::;;;;;;;:::,,.                    H#s:;isS92:.     ;hAiirr;i2:   ,;                  ;:   2                              P                                       .,,,::;;;;;;;:;::,,..   s@@G           .;:.   ,sX,    .X;::,,....          ;:   2                              P                                                      ..,,::;;:.X@@@&      ,;:.     :;,    .s:    ..,,::::;;;;;;;:h:   5                              P                                                                  r@@@..:r:ii;:;ii;;.     ;2                           2                              P                                                                     .,,.  @@#5         .ri,:;;;;;;::::.,..            5                              P                                                                           3@@@@r     ,s;          ...,,,::;;;;;;;;;:,,A                              P                                                                            ;@@@@@; ,r;                            ...,,                              P                                                                              ,X#@@r:                                                                 PU" };

	int i = 0;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == 'P')
		{
			a[i] = '|';
		}
	}
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == '|')
		{
			a[i + 1] = '\n';
		}

		printf("%c", a[i]);
	}
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf(" 평화로운 어느날, 공주님의 집에 도리베어가 살고있엇어요.");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                                                                                                  .X02.      77                  8X                  |\n");
	printf("                                                                                                 X8:                            82                   |\n");
	printf("                                                                                               .Br                             20                    |\n");
	printf("                                                                                              .B.                             .B                     |\n");
	printf("                                                                                              B.                              X7                     |\n");
	printf("                                                                                             B:                 7          rX7B                      |\n");
	printf("                                                                                            Bi                 .B            .Br                     |\n");
	printf("                                                                                           B7                   B              Bi                    |\n");
	printf("                                                                                          87     7S2227         Z7              B                    |\n");
	printf("                                                                                         rM     B7    rB777r.    Bi             S2                   |\n");
	printf("                                                                                         B.    B:    02:. .:07    87            .B                   |\n");
	printf("                                                                                         B    M2    B:       B0227.2X            B                   |\n");
	printf("                                                                                        70   .2    B:      7Zi    rr.27.         B                   |\n");
	printf("                                                              r2XS2.                    8:        87      M2      rS7777i       :B                   |\n");
	printf("                                                             M2.  :Bi                   B        iB     :B.     0X.  .M.        B.                   |\n");
	printf("                                                   i22222i  :M      B                   2X       B.    :B      B:      7       X2                    |\n");
	printf("                                          .i:    XZ2.. .:7SXMB      B                    0X     70     B      B.   :iriiii    rB                     |\n");
	printf("                                        70X77X27Bi          .r00:  2M                     r02r77B     02     B  rS2ri...ir.  .B                      |\n");
	printf("                                       BS     BZ               .X0MX                        .:. M     B     27.X:            B                       |\n");
	printf("                                      20     rB                   MX        202.                B    27     B 02:.         .B.                       |\n");
	printf("                                      XZ     B:                    7B      ZBBBB7               i07: Bi     B   .7777i   :2M                         |\n");
	printf("                                       08:   B             72 7S    :B    .8iBBBB                 :720B.    0X      Br2227:                          |\n");
	printf("                                        .2077B      S       rBB.     2M   22 XBBB:                     XX7. 0S227iiB.                                |\n");
	printf("                                           7B    .2B7       r2.0M.    B   B    rB.                       i22i   .:i                                  |\n");
	printf("                                           B      MM7X7         .     Mi 0X     B                                                                    |\n");
	printf("               2S          8B             :B     .B   : :8B           B rB     Br                                                                    |\n");
	printf("               .BX.        BBi            7Z            7BB           BX0     MX                                                                     |\n");
	printf("                M:X0:     B7 B            :B                         BB:     BS                                                                      |\n");
	printf("                Xr .2XX2S07  :B2riiXX      B:                      .BZ     7B:                                                                       |\n");
	printf("                7X     .       ..:BB        B.                   .08B7   :M0                        ii                                               |\n");
	printf("                S2               M7         .B7               .2Z0:  iMXS2                          2Z                                               |\n");
	printf("                B.              02            2B2         .i20Xr       B2                           2S      .                                        |\n");
	printf("               :M            .: B               70X27770BMBX            8X                          BB     B7                                        |\n");
	printf("               B772S27     002r7Br                    XBr  8             XB                        :BBi  :XB.                                        |\n");
	printf("             :B8:.   rB7 .Bi    :7                  :M7    B              7B             7M       2B  2XS2 Zi                                        |\n");
	printf("             7.        B2B                        78X    iZB:              rB            .8BMr77X02        .B                                        |\n");
	printf("                        Br                 .:ir2SSr    .M0 22               B               Bi .            iBi                                      |\n");
	printf("                        B:                08..       .0M:  22               B2               B                8B:                                    |\n");
	printf("                        B2                .BBBBBX. r8Z:    X2               B7B:             B.            7X2i0B.                                   |\n");
	printf("                        B7                  XBBBBB07.      7Z              Zr  B2            Mr           BX                                         |\n");
	printf("                                                            B             2B    B2           B   ...     ZX                                          |\n");
	printf("                                                            B7           B2 B    Br         .B22X222XXS. B                                           |\n");
	printf("                                                             B:       .XB:  XS    B        .B7        :0BM                                           |\n");
	printf("                                                              077::i20X:     B    BX                    0B                                           |\n");
	printf("                                                               080B:.        B   BBB                     B                                           |\n");
	printf("                                                              82 72          87 7BBS                     i                                           |\n");
	printf("                                                             B2  B:          .B BBB                                                                  |\n");
	printf("                                                           .Br   B            02BB.                                                                  |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------|\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf(" 저런! 공주님이 또 화가 났나 봐요. 도리베어 한테 화를 풀고 있네요");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                                                                                                                                                     |\n");
	printf("::rri:.                                                                                                                                              |\n");
	printf("BBBBQBBBBBEr                                                            .r7sv7i:                                                                     |\n");
	printf("i:...:rUQBBBBBv                                                    igBBBBBBBBBBBBBBZr                                                  iPBBBBQBQBBBQR|\n");
	printf("           rQBBBX                                               rBBBBBMJ:.   ..iJRBBQBBr                                            2BBBBBBgSJvsjPQBB|\n");
	printf("              2BBBL                                           uBBQBr                rQBBBY                                       :BBBBMi             |\n");
	printf("                PBBB                                        :BBBX                      PBBB:                                    BBBBi                |\n");
	printf("                 :BBB                                      qBBB                          BBQX                                 vBBB:                  |\n");
	printf("                   BBB                                    gBBY                            JBBg                               PQBb                    |\n");
	printf("                   :BQI                                  qBBr                              7BBX                             5QBJ                     |\n");
	printf("                    RBB                                 .BBq                                qBB.                           :BBP                      |\n");
	printf("                    .BB7                                BBB                                  BBB                           QBB                       |\n");
	printf("                     BBg                                QB1                                  KBB                          .BBv                       |\n");
	printf("                     BBQ                               iBB:                                  :BBi                         1BB                        |\n");
	printf("                     BBE                               rBB.                                  .BBr                         bBB                        |\n");
	printf("                    .BBr                               :BB:                                  iBQ:                         SBB                        |\n");
	printf("vLvsLJsjs1jU122IU2siBBB                                 BBq                                  ZQB                          :BB:                       |\n");
	printf("QRQRQgMDgDDEZddPP27BBB7                                 gBB.i7YLjJ1u11I252S5X5KSKXqKbPdbEbdULBBb                           BBQ        . .............|\n");
	printf("                   BBR                                   BQB5PZgDgDgDgEDdZPdPPKqXqSX5S2I1j7rBBB                            LBBQBBBBBBBBBBBBBBBQBBBBBB|\n");
	printf("                 rBBB                                    :BBY                              JBB:                             BBB                      |\n");
	printf("                MBBq                                      rBBR                            QBBr                               BQB.                    |\n");
	printf("              dBBB:                                        .BBBi                        rBBB.                                 QBB2                   |\n");
	printf("           jBBQB7                                            ZBBQr                    rBBBP                                    vBBBv                 |\n");
	printf("vri:i7uZBBBBBZ:                                                gBBBgi              iQQBBg                                        XBBBd:              |\n");
	printf("QBQBQBBBBQv.                                                     YBBBBBBZIL7rs2DBBBBBBv                                            YBBBBQPr:     .:JR|\n");
	printf("  ..                                                                :IBBBBBBBBBBBBI:                                                  7RBQBBBBBQBBBBB|\n");
	printf("                                                                                                                                           .:77vr:.  |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                          :vUu.                             ..                                                                       |\n");
	printf("                                         Kq. .Zr :7sj1sLi.             .uS2IYj2q7                                                                    |\n");
	printf("                                         Q    vB27i.....7qZ:     . rXjSP:       YB:                                                                  |\n");
	printf("                                         Q. 1Dr           .bZ 7RUM2U              Bi  .iirrrii..                                                     |\n");
	printf("                                          QBr               rQg.r                  BPri::::::rvuS2s:                                                 |\n");
	printf("                                         .B        :1        JD                    :B             :v2qJ:                                             |\n");
	printf("                                         Q.        .B  7P     B.                    QPrvu15jr         .vdL                                           |\n");
	printf("                                         B       i.    Br     rR                    I:     .rXq7         IB                                          |\n");
	printf("                                        ig       iU     Xi     B                    Z.         rPPr   Yu7.B7                                         |\n");
	printf("                                         B        :  X         B                    B7i7ri:.      sD7Br   Q.                                         |\n");
	printf("                                         SP         .B        :D                   UB ..:irvIXJ.    rPjuuI.                                          |\n");
	printf("                                          SP         .        XB7JuKqUuIUUj2suYsvvJBb         :2bu                                                   |\n");
	printf("                                           7Br                B v..          .....  .2Pv         :EK                                                 |\n");
	printf("                                           Q r51Y2L11I2s.    B:                        rbP:        iQ.                                               |\n");
	printf("                                           B    .Q     rEX7vQ:                           .qdr       7B.                                              |\n");
	printf("                                           :gY:id7        ::                                sM7     g.B                                              |\n");
	printf("                                             .ii                                              2Q   r2 UU                                             |\n");
	printf("                                                                                               :B: :5 vK                                             |\n");
	printf("                                                                                                 R1 g Zr                                             |\n");
	printf("                                                                                                  iIBZE                                              |\n");
	printf("                                                                                                     .                                               |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------|\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf("변기에 빠진 도리베어는 정신을 차려보니 팔이 사라진 채 하수구에 쓰러져있었어요.");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                    iBB7                                7BBv                               BBB                               BBB                     |\n");
	printf("                     BBB                                BBB                                 BBq                             .BBU                     |\n");
	printf("                     jBB                               vQB.                                 XBB                             BBB                      |\n");
	printf("                     :QB:                              BBB                                   BBv                            BBL                      |\n");
	printf("                     .BBi                              BBQ                                   BBE                           7BB                       |\n");
	printf("                     rBB.                              BBM                                   BBE                           LBB                       |\n");
	printf("                     QBQ                               BBB                                   BQu                           rBB.                      |\n");
	printf("QQQBBBBBBBBBBBBBBBBgPBQU                               sBB                                  vBB                             BB1                      |\n");
	printf("v7v77r7rrrririii::..BBB                                 BBB2gBQBBBBBBBBBBBBBBBBBQBBBBBBBBBBZBBB                             BBB.:rr77vvvvYYsYjsuj112U|\n");
	printf("                   gBB                                  vBBQ.irr7rrrririiii:i::::::::....  BBQ                               BBBKgQBBQBQBQQMQMMgMZDZZ|\n");
	printf("                  BBB.                                   EBB.                             uBBi                               LBB:                    |\n");
	printf("                UBBB                                      EBBU                           BBBr                                 2BB5                   |\n");
	printf("              SBBQL                                        vQBB:                       LBBB.                                   rBBQ.                 |\n");
	printf("          .5QBBBs                                            RBBBr                   uBBBU                                       BBBB.               |\n");
	printf("BBRPEDBBBQBBBE:                                               .gQBBBL.           :IBQBBI                                          .BBBBK.            |\n");
	printf("BBQBQBBBBSi                                                      rBBBQBBBBBQBBBBBBBBg:                                               5BBBBBRSvrii7JqB|\n");
	printf("                                                                     rXBBBBBBBBQ1i                                                      rDQBBBBBBBBBB|\n");
	printf("                                 .iii:.                                                                                                              |\n");
	printf("                              .ISsiiirLX5.              iYLLr:          ..::::...            .::                                                     |\n");
	printf("                             rg.        :Qr           1br...:r1LirK5PUUJs77r7r7vJu51Yi     vPsr7Ev                                                   |\n");
	printf("                             Pr           B          YD       iBv...                .7SP::X:     gL                                                  |\n");
	printf("                             .B           B          B      .d2                         rBI       B                                                  |\n");
	printf("                            iE.          Ss          Zs    jg.                        .   .Kq:    B                                                  |\n");
	printf("                            B            .:r          5Pi PI                       I  sQ :. .dP  :B         .Y2j1                                    |\n");
	printf("                            Pv           YQB            .Z5                     ..7B   L7i    LB7X         Yd:  :QbJjJ                               |\n");
	printf("                             Qv    .Ms  .MQ             YP                      Ur.       .    uB         iQ      s  rBr                             |\n");
	printf("                              7u1Ujv:B SS.             MU                         7YP. vgr7     LZ        :g           PI                            |\n");
	printf("                                     UQ.             rB.                          . :B 1Y        Rr        Q.           B                            |\n");
	printf("                                                    qZ                               s            B         g.          Q.                           |\n");
	printf("                                                   gU                                             5U       I7B         Lg                            |\n");
	printf("                                                  Ms             .                                 B       MK: :     :PK                             |\n");
	printf("                                                 PU             .j1u2I:      7sJ2USr               B        iBv5K7LuXu.                              |\n");
	printf("                                                :B                                                 B             ..                                  |\n");
	printf("                                                B.                                                rg                                                 |\n");
	printf("                                                Q                        :::                      B.                                                 |\n");
	printf("                                                B                      DB...B7                   iQ                                                  |\n");
	printf("                                                15                      r7 rI.                   B                                                   |\n");
	printf("                                                 B                      rQB.                    B.                                                   |\n");
	printf("                                                 :Q                  .jDi  gr                  B:                                                    |\n");
	printf("                                                  rB.                77     S5               :B:                                                     |\n");
	printf("                                                   .ZX.                                    :PE                                                       |\n");
	printf("                                                     .5Ks:                               7ES.                                                        |\n");
	printf("                                                        :vU5uLi.                      rqq7                                                           |\n");
	printf("                                                            ..i77BqjuLvrrii::...::rsBLi                                                              |\n");
	printf("                                                                rI   ..::rr77v7v7r: vI                                                               |\n");
	printf("                                                               .B                    5U                                                              |\n");
	printf("                                                              7P                       B                                                             |\n");
	printf("                                                              Q.                       Ij                                                            |\n");
	printf("                                                             :g                         Q.                                                           |\n");
	printf("                                                             :Z                         s5                                                           |\n");
	printf("                                                             iE                          B                                                           |\n");
	printf("                                                             :D                          R.                                                          |\n");
	printf("                                                              B                          Zr                                                          |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("과연 도리베어는 팔을 찾고 공주님을 물리칠 수 있을까요?");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");
	return;

}
int roommove(room)
{
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ＼     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 하수구");
	gotoxy(x, y + 1);
	printf("   가운데 하수구");
	gotoxy(x, y + 2);
	printf("   오른쪽 하수구");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				room = 1;
				return room;

			}
			else if (y == 51) {
				room = 2;
				return room;
			}
			else if (y == 52) {
				room = 3;
				return room;
			}
		}
		}
	}
}
int cRoom1(room)   //c 많은 하수구
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ＼     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("여기는 c가 많은 하수구야. 이 하수구로 들어갈까?");
	gotoxy(x, y);
	printf("▶ 예");
	gotoxy(x, y + 1);
	printf("   아니오");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("▶ 왼쪽 길");
				gotoxy(x, y + 1);
				printf("   가운데 길");
				gotoxy(x, y + 2);
				printf("   오른쪽 길");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, --y);
							printf("▶");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, ++y);
							printf("▶");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
							cRoomA1();
							break;
						}
						else if (y == 51) {
							cRoomA2();
							break;
						}
						else if (y == 52) {
							cRoomA3();
						}
					}
					}
				}
			}
			else if (y == 52) {
				roomin = 1;
				return roomin;
			}
		}
		}
	}
}
int gRoom1()  // G417 하수구
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i:,,:::    i,  .,i,      a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     7     .XiiX:      7      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,i      X  ;r      7      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r...,,r,   rr::::;,      Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0      ::,..r,,,,i.            8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX           ..     :         Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       .r:::i;:ii:        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("여기는 G417 하수구야. 이 하수구로 들어갈까?");
	gotoxy(x, y);
	printf("▶ 예");
	gotoxy(x, y + 1);
	printf("   아니오");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("▶ 왼쪽 길");
				gotoxy(x, y + 1);
				printf("   가운데 길");
				gotoxy(x, y + 2);
				printf("   오른쪽 길");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, --y);
							printf("▶");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, ++y);
							printf("▶");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
							gRoomA1();
							break;
						}
						else if (y == 51) {
							gRoomA2();
							break;
						}
						else if (y == 52) {
							gRoomA3();
						}
					}
					}
				}
			}
			else if (y == 52) {
				roomin = 1;
				return roomin;
			}
		}
		}
	}
}
int nRoom1()  // 그냥 하수구
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ＼     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("여기는 평범한 하수구야. 이 하수구로 들어갈까?");
	gotoxy(x, y);
	printf("▶ 예");
	gotoxy(x, y + 1);
	printf("   아니오");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("▶ 왼쪽 길");
				gotoxy(x, y + 1);
				printf("   가운데 길");
				gotoxy(x, y + 2);
				printf("   오른쪽 길");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, --y);
							printf("▶");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, ++y);
							printf("▶");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
							nRoomA1();
							break;
						}
						else if (y == 51) {
							nRoomA2();
							break;
						}
						else if (y == 52) {
							nRoomA3();
						}
					}
					}
				}
			}
			else if (y == 52) {
				roomin = 1;
				return roomin;
			}
		}
		}
	}
}

int cRoomA1() // C통로들 ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 항아리");
	gotoxy(x + 15, 50);
	printf("항아리는 항아리");
	gotoxy(x, y + 1);
	printf("   상자");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				pot();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("항아리는 항아리");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("상자는 상자");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 종이조각");
	gotoxy(x + 15, 50);
	printf("종이조각은 종이조각");
	gotoxy(x, y + 1);
	printf("   항아리");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				paper();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("종이조각은 종이조각");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("항아리는 항아리");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 종이조각");
	gotoxy(x + 15, 50);
	printf("종이조각은 종이조각");
	gotoxy(x, y + 1);
	printf("   상자");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				paper();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("종이조각은 종이조각");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("상자는 상자");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 책장");
	gotoxy(x + 15, 50);
	printf("책장은 책장");
	gotoxy(x, y + 1);
	printf("   이상한 사람");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				bookshelf();
				k = 0;
			}
			else if (y == 51) {
				stranger();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("책장은 책장");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("Strange People");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				cRoomC1();
			}
			else if (y == 51) {
				cRoomC2();
			}
			else if (y == 52) {
				cRoomC3();
			}
		}
		}
	}
}

int cRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 상자");
	gotoxy(x + 15, 50);
	printf("상자는 상자");
	gotoxy(x, y + 1);
	printf("   책장");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				box();
				k = 0;
			}
			else if (y == 51) {
				bookshelf();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("상자는 상자");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("책장은 책장");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				cRoomC1();
			}
			else if (y == 51) {
				cRoomC2();
			}
			else if (y == 52) {
				cRoomC3();
			}
		}
		}
	}
}

int cRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 구덩이");
	gotoxy(x + 15, 50);
	printf("구덩이는 구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				hole();
				k = 0;
			}
		}
		}
		k++;
		Sleep(3000);
		system("cls");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                       :77vvvvL77i.                                                                 |\n");
		printf("                                                                    iUYi.       .:7us:                                                              |\n");
		printf("                                                                  rXr                rSv                                                            |\n");
		printf("                                                                 q7                    iK7                                                          |\n");
		printf("                                                               .d.                       LP                                                         |\n");
		printf("                                                              :d                          .g.                                                       |\n");
		printf("                                                             .Z                             R.                                                      |\n");
		printf("                                                             M                        .      Q                                                      |\n");
		printf("                                                            D.       .                .Ir    .D                                                     |\n");
		printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
		printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
		printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
		printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
		printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
		printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
		printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
		printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
		printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
		printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
		printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
		printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
		printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
		printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
		printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
		printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
		printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
		printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
		printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
		printf("           g                                                        1U7B           .B                                                     :X        |\n");
		printf("           7s                                                        uB             :B      BB                                            P.        |\n");
		printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
		printf("             g                                                     BP                B                                                   Y7         |\n");
		printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
		printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
		printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
		printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
		printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
		printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
		printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
		printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
		printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
		printf(" :U7                                                                    Bi          B                                                             YL|\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		x = 0, y = 50;
		gotoxy(x, y);
		printf("▶ 왼쪽 통로");
		gotoxy(x, y + 1);
		printf("   가운데 통로");
		gotoxy(x, y + 2);
		printf("   오른쪽 통로");
		while (1) {
			int n = keycontrol();
			switch (n) {
			case UP: {
				if (y > 50) {
					gotoxy(x, y);
					printf("   ");
					gotoxy(x, --y);
					printf("▶");
				}
				break;
			}
			case DOWN: {
				if (y < 52) {
					gotoxy(x, y);
					printf("   ");
					gotoxy(x, ++y);
					printf("▶");
				}
				break;
			}
			case SUBMIT: {
				if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
					cRoomC1();
				}
				else if (y == 51) {
					cRoomC2();
				}
				else if (y == 52) {
					cRoomC3();
				}
			}
			}
		}
	}
}

int cRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 파이프");
	gotoxy(x + 15, 50);
	printf("파이프는 파이프");
	gotoxy(x, y + 1);
	printf("   쥐구멍");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("파이프는 파이프");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int cRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 고인물");
	gotoxy(x + 15, 50);
	printf("고인물은 고인물");
	gotoxy(x, y + 1);
	printf("  쥐구멍");
	gotoxy(x, y + 2);
	printf("  항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("고인물은 고인물");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int cRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 쥐구멍");
	gotoxy(x + 15, 50);
	printf("쥐구멍은 쥐구멍");
	gotoxy(x, y + 1);
	printf("   항아리");
	gotoxy(x, y + 2);
	printf("   상자");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("항아리는 항아리");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("상자는 상자");
			}
		}
	}
	k++;

	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");

	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}


int gRoomA1() // G417통로들 ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 상자");
	gotoxy(x + 15, 50);
	printf("상자는 상자");
	gotoxy(x, y + 1);
	printf("   구덩이");
	gotoxy(x, y + 2);
	printf("   종이조각");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				box();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				paper();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("상자는 상자");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("구덩이는 구덩이");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("종이조각은 종이조각");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 쥐구멍");
	gotoxy(x + 15, 50);
	printf("쥐구멍은 쥐구멍");
	gotoxy(x, y + 1);
	printf("   항아리");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("항아리는 항아리");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 구덩이");
	gotoxy(x + 15, 50);
	printf("구덩이는 구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 이상한 원");
	gotoxy(x + 15, 50);
	printf("이상한 원은 이상한 원");
	gotoxy(x, y + 1);
	printf("   상자");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				circle();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("이상한 원은 이상한 원");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("                     ");
				gotoxy(x + 15, 51);
				printf("상자는 상자");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 이상한 사람");
	gotoxy(x + 15, 50);
	printf("Stranger");
	gotoxy(x, y + 1);
	printf("   항아리");
	gotoxy(x, y + 2);
	printf("   상자");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				Gstranger();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("Stranger");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("항아리는 항아리");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("상자는 상자");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 이상한 사람");
	gotoxy(x + 15, 50);
	printf("Stranger");
	gotoxy(x, y + 1);
	printf("   이상한 원");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				Gstranger();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                      ");
				gotoxy(x + 15, 50);
				printf("Stranger");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("                     ");
				gotoxy(x + 15, 51);
				printf("이상한 원은 이상한 원");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 파이프");
	gotoxy(x + 15, 50);
	printf("파이프는 파이프");
	gotoxy(x, y + 1);
	printf("   쥐구멍");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("파이프는 파이프");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int gRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 고인물");
	gotoxy(x + 15, 50);
	printf("고인물은 고인물");
	gotoxy(x, y + 1);
	printf("  쥐구멍");
	gotoxy(x, y + 2);
	printf("  상자");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("고인물은 고인물");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("상자는 상자");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int gRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 종이조각");
	gotoxy(x + 15, 50);
	printf("종이조각은 종이조각");
	gotoxy(x, y + 1);
	printf("   구덩이");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				paper();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("종이조각은 종이조각");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("구덩이는 구덩이");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomA1() // 그냥 통로들 ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 종이조각");
	gotoxy(x + 15, 50);
	printf("종이조각은 종이조각");
	gotoxy(x, y + 1);
	printf("   상자");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				paper();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("종이조각은 종이조각");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("상자는 상자");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 쥐구멍");
	gotoxy(x + 15, 50);
	printf("쥐구멍은 쥐구멍");
	gotoxy(x, y + 1);
	printf("   항아리");
	gotoxy(x, y + 2);
	printf("   구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("항아리는 항아리");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 상자");
	gotoxy(x + 15, 50);
	printf("상자는 상자");
	gotoxy(x, y + 1);
	printf("   구덩이");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				box();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("상자는 상자");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("구덩이는 구덩이");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 스위치");
	gotoxy(x + 15, 50);
	printf("스위치는 스위치");
	gotoxy(x, y + 1);
	printf("   구덩이");
	gotoxy(x, y + 2);
	printf("   이상한 사람");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				button();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				stranger();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("스위치는 스위치");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("구멍은 구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("Strange People");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				nRoomC1();
			}
			else if (y == 51) {
				nRoomC2();
			}
			else if (y == 52) {
				nRoomC3();
			}
		}
		}
	}
}

int nRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 상자");
	gotoxy(x + 15, 50);
	printf("상자는 상자");
	gotoxy(x, y + 1);
	printf("   스위치");
	gotoxy(x, y + 2);
	printf("   종이조각");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				box();
				k = 0;
			}
			else if (y == 51) {
				button();
				k = 0;
			}
			else if (y == 52) {
				paper();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("상자");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("스위치");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("종이조각은 종이조각");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 왼쪽 통로");
	gotoxy(x, y + 1);
	printf("   가운데 통로");
	gotoxy(x, y + 2);
	printf("   오른쪽 통로");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				nRoomC1();
			}
			else if (y == 51) {
				nRoomC2();
			}
			else if (y == 52) {
				nRoomC3();
			}
		}
		}
	}
}

int nRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 이상한 사람");
	gotoxy(x + 15, 50);
	printf("Strange People");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				hole();
				k = 0;
			}
		}
		}
		k++;
		Sleep(3000);
		system("cls");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                       :77vvvvL77i.                                                                 |\n");
		printf("                                                                    iUYi.       .:7us:                                                              |\n");
		printf("                                                                  rXr                rSv                                                            |\n");
		printf("                                                                 q7                    iK7                                                          |\n");
		printf("                                                               .d.                       LP                                                         |\n");
		printf("                                                              :d                          .g.                                                       |\n");
		printf("                                                             .Z                             R.                                                      |\n");
		printf("                                                             M                        .      Q                                                      |\n");
		printf("                                                            D.       .                .Ir    .D                                                     |\n");
		printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
		printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
		printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
		printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
		printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
		printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
		printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
		printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
		printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
		printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
		printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
		printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
		printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
		printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
		printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
		printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
		printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
		printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
		printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
		printf("           g                                                        1U7B           .B                                                     :X        |\n");
		printf("           7s                                                        uB             :B      BB                                            P.        |\n");
		printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
		printf("             g                                                     BP                B                                                   Y7         |\n");
		printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
		printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
		printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
		printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
		printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
		printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
		printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
		printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
		printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
		printf(" :U7                                                                    Bi          B                                                             YL|\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		x = 0, y = 50;
		gotoxy(x, y);
		printf("▶ 왼쪽 통로");
		gotoxy(x, y + 1);
		printf("   가운데 통로");
		gotoxy(x, y + 2);
		printf("   오른쪽 통로");
		while (1) {
			int n = keycontrol();
			switch (n) {
			case UP: {
				if (y > 50) {
					gotoxy(x, y);
					printf("   ");
					gotoxy(x, --y);
					printf("▶");
				}
				break;
			}
			case DOWN: {
				if (y < 52) {
					gotoxy(x, y);
					printf("   ");
					gotoxy(x, ++y);
					printf("▶");
				}
				break;
			}
			case SUBMIT: {
				if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
					cRoomC1();
				}
				else if (y == 51) {
					cRoomC2();
				}
				else if (y == 52) {
					cRoomC3();
				}
			}
			}
		}
	}
}

int nRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 파이프");
	gotoxy(x + 15, 50);
	printf("파이프는 파이프");
	gotoxy(x, y + 1);
	printf("   쥐구멍");
	gotoxy(x, y + 2);
	printf("   상자");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("파이프는 파이프");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("상자는 상자");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 고인물");
	gotoxy(x + 15, 50);
	printf("고인물은 고인물");
	gotoxy(x, y + 1);
	printf("  쥐구멍");
	gotoxy(x, y + 2);
	printf("  구덩이");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("고인물은 고인물");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("구덩이는 구덩이");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("▶ 쥐구멍");
	gotoxy(x + 15, 50);
	printf("쥐구멍은 쥐구멍");
	gotoxy(x, y + 1);
	printf("   구덩이");
	gotoxy(x, y + 2);
	printf("   항아리");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("쥐구멍은 쥐구멍");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("구덩이는 구덩이");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("항아리는 항아리");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("보스전으로 출발합니다");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int bagprint()
{
	int i = 0;
	if (strstr(Player.items, "Som") != 0)
	{
		strcpy(haveitem[i], "솜뭉치");
		strcpy(itemeffect[i], "체력 10를 회복한다.");
		whatitemuse[i][1] = 0;
		i++;
	}
	if (strstr(Player.items, "Gum") != 0)
	{
		strcpy(haveitem[i], "껌");
		strcpy(itemeffect[i], "보호막 10의 수치를 얻는다.");
		whatitemuse[i][1] = 1;
		i++;
	}
	if (strstr(Player.items, "Inssa") != 0)
	{
		strcpy(haveitem[i], "인싸토끼모자");
		strcpy(itemeffect[i], "귀여움이 상승한다.");
		whatitemuse[i][1] = 2;
		i++;
	}
	if (strstr(Player.items, "IceCream") != 0)
	{
		strcpy(haveitem[i], "아이스크림");
		strcpy(itemeffect[i], "체력 15를 회복한다.");
		whatitemuse[i][1] = 6;
		i++;
	}
	if (strstr(Player.items, "MagicCircle") != 0)
	{
		strcpy(haveitem[i], "매직 서클");
		strcpy(itemeffect[i], "보스에게 큰 데미지를 준다.");
		whatitemuse[i][1] = 4;
		i++;
	}
	if (strstr(Player.items, "Freport") != 0)
	{
		strcpy(haveitem[i], "F맞은 성적표");
		strcpy(itemeffect[i], "어떤 패시브가 있으면 쓸 수 있을것 같다...");
		whatitemuse[i][1] = 5;
		i++;
	}
	if (strstr(Player.items, "Infinity") != 0)
	{
		strcpy(haveitem[i], "인피니티 건틀릿");
		strcpy(itemeffect[i], "둘 중에 하나는...");
		whatitemuse[i][1] = 3;
		i++;
	}
	if (i == 0)
	{
		strcpy(haveitem[i], "없어용");
		strcpy(itemeffect[i], "힝 없어용");
		whatitemuse[i][1] = 9;
		i++;
	}
	if (i == 1)
	{
		strcpy(haveitem[i], "없어용");
		strcpy(itemeffect[i], "힝 없어용");
		whatitemuse[i][1] = 9;
		i++;
	}
	if (i == 2)
	{
		strcpy(haveitem[i], "없어용");
		strcpy(itemeffect[i], "힝 없어용");
		whatitemuse[i][1] = 9;
		i++;
	}

}
int gum(int playerHP) // 아이템 효과  : 껌------------------------------
{
	int a = playerHP + 10;
	return a;
}

int som(int playerHP) // 아이템 효과 : 솜뭉치
{
	int a = playerHP + 10;
	if (a >= 50)
	{
		a = 50;
	}
	return a;
}

int inssa(int bosspower) // 아이템 효과 : 인싸토끼모자
{
	int a = bosspower - 1;
	return a;
}

int icecream(int playerHP) // 아이템 효과 : 아이스크림
{
	int a = playerHP + 15;
	if (a >= 50)
	{
		a = 50;
	}
	return a;
}

int magiccircle(int bossHP) // 아이템 효과 : Magic Circle
{
	int a = bossHP - 50;
	return a;
}

int Freport() // 아이템 효과 : F맞은 성적표
{
	if (Player.passive == DropC)
	{
		PlaySound(NULL, 0, 0);
		system("cls");
		SPEnd07();
	}
	else
	{
		gotoxy(65, 47);
		printf("                                         ");
		gotoxy(65, 48);
		printf("                                         ");
		gotoxy(65, 49);
		printf("                                         ");
		gotoxy(65, 50);
		printf("                                         ");
		gotoxy(65, 48);
		printf("공주가 분노 했다!!");
		Sleep(3000);
		gotoxy(65, 48);
		printf("공주의 공격력이 5 상승했다!!");
		Sleep(3000);
		gotoxy(65, 48);
		printf("                                         ");
	}
}

int infinity() // 아이템 효과 : 인피니티 건틀렛
{
	srand(time(NULL));
	whatitem = whodie[rand() % 2];
	if (whatitem == 0)
	{
		PlaySound(NULL, 0, 0);
		SPEnd10();
	}
	else if (whatitem == 1)
	{
		PlaySound(NULL, 0, 0);
		SPEnd11();
	}
}

int boss() // 보스전------------------------------------------------------------------
{
	if (Player.arms == NULL)
	{
		BadEnd01();
	}
	PlaySound(TEXT(SANSBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int bossHP = 200;
	int playerHP = 50 + cheese;
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                     .27    :    :                                  |\n");
	printf("                                                                                              .:ri. iK vX  7QU .bP7                                 |\n");
	printf("                                                                                             2u: .sb7   iXu1 jSb  Pr  :uv77jY                       |\n");
	printf("                                                                                           rP.    2D     .7   b    q.i7     :g                      |\n");
	printf("                                                                                          rX    iJ75:               BB       i5                     |\n");
	printf("                                                                                          R    S7   rssri..     ..7U. YU.     g                     |\n");
	printf("                                                                                          7U  D.       ..:irr777ii.    .d:   2L                     |\n");
	printf("                                                                                           77d:                s         g :Iv                      |\n");
	printf("                                                                                            .R          :D     Mj        .b                         |\n");
	printf("                                                                                            si      .Y.YjM   M2: UIj      d                         |\n");
	printf("                                                                                            K.     .Sj  .2 :iP    LR.     v7                        |\n");
	printf("                                                                                            J: j7:.i    .:.         17  i J:                        |\n");
	printf("                                                                                             qiKv iBQBBBBBBBBBQBBBBB i75QiB                         |\n");
	printf("                                                                                             D ui gBBBBBBBBBBQBBBBBR   i1 g                         |\n");
	printf("                                                                                             v:P  BBQBBBQBBBBBBBBBBB   iDrL                         |\n");
	printf("                                                                                              rS  gBBBBBBQBBBBBBBQBZ   2s                           |\n");
	printf("                                                                                              D    UEQBBBBQBBBBBQBM    R                            |\n");
	printf("                                                                                             i2                      .R.                            |\n");
	printf("                                                                                             LY                    .Yq                              |\n");
	printf("                                                                                              b7                 i1u:                               |\n");
	printf("                                                                                               isj7r::.. ....ri7r.                                  |\n");
	printf("                                                                                                    .:rrPQMvQjbi:.                                  |\n");
	printf("                                                                                                   .ir.g.  .  :J :Uv                                |\n");
	printf("                                                                                                 :27. :i       D   :1Y:                             |\n");
	printf("                                                                                               .2L    uI.    :DSri    rUi                           |\n");
	printf("                                                                                             .s7   .7riIjr777: :sLL:    rK                          |\n");
	printf("                                                                                             uK  iJr iY          Yv:7vrrib                          |\n");
	printf("                                                                                              .ir:  jv            vL                                |\n");
	printf("                                                                                                   d:              u7                               |\n");
	printf("                                                                                                  g.                Q                               |\n");
	printf("                                                                                                 5:                 D                               |\n");
	printf("                                                                                                 D.               .X.                               |\n");
	printf("                       .v7ir  :irri:.  .v77Jr                                                     r5vi.... . ..iiYB.                                |\n");
	printf("                      rS  rgZri:..::rvjQi   :b.                                                    P. .Q2irrriigv  1L                               |\n");
	printf("                     .D  Pi             rX:   Q                                                  .Z   :u        JJ  :qr                             |\n");
	printf("                     ur :I                2j iI                                                 .g   .D          rq   rs7rrP                        |\n");
	printf("                     .P.Lr                 iBi                                                 :Z    R            .d.     .E                        |\n");
	printf("                        D.                  .q                                               Yvi   .M               IJ.  iE                         |\n");
	printf("                       .b                    iq                                             .B    rE                 .vvvr                          |\n");
	printf("                      7b                      Z.                                              77vYr                                                 |\n");
	printf("                    .d7                       vL                                                                                                    |\n");
	printf("                    Q                         E.                                                                                                    |\n");
	printf("                   u7                        iq                                                                                                     |\n");
	printf("                   I:                       rd                                                                                                      |\n");
	printf("                   .M                      Xj                                                                                                       |\n");
	printf("                    ib.                 .Jj.                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-|\n");
	printf("                     .uUr.           .i1vIv                    l                                            l                                       |\n");
	printf("                        :rsLviviri7vJLr   rP                   l                                            l                                       |\n");
	printf("                             :M....        rE                  l                                            l                                       |\n");
	printf("                             q.             7X                 l                                            l                                       |\n");
	printf("                            .d               Kr                l                                            l                                       |\n");
	printf("                            Z.                Q                l                                            l                                       |\n");
	printf("                           .D                 ur               l                                            l                                       |\n");
	printf("                           Kr                 rX               l                                            l                                       |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(10, 5);
	printf("보스 HP : %d", bossHP);
	gotoxy(10, 10);
	printf("플레이어 HP : %d", playerHP);
	x = 115, y = 47;
	gotoxy(x, y);
	printf("▶ 기본공격");
	gotoxy(x - 50, y + 1);
	printf("공주에게 기본 공격을 가한다!");
	gotoxy(x, y + 3);
	printf("   특수공격");
	gotoxy(x + 15, y);
	printf("   방어하기");
	gotoxy(x + 15, y + 3);
	printf("   가방보기");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 47)
			{
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, y - 3);
				printf("▶");
				y = y - 3;
			}
			break;
		}
		case DOWN: {
			if (y < 50) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, y + 3);
				printf("▶");
				y = y + 3;
			}
			break;
		}
		case LEFT: {
			if (x > 115) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x - 15, y);
				printf("▶");
				x = x - 15;
			}
			break;
		}
		case RIGHT: {
			if (x < 130) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x + 15, y);
				printf("▶");
				x = x + 15;
			}
			break;
		}
		case SUBMIT: {
			if (x == 115 && y == 47) {
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("도리베어는 일반 공격을 했다!");
				Sleep(1500);
				if (Player.arms == DoriArms)
				{
					bossHP = bossHP - 15;
					whatdamage = 15;
				}
				else if (Player.arms == Wings)
				{
					bossHP = bossHP - 20;
					whatdamage = 20;
				}
				else if (Player.arms == Twigs)
				{
					bossHP = bossHP - 10;
					whatdamage = 10;
				}
				else if (Player.arms == CatArms)
				{
					bossHP = bossHP - 20;
					whatdamage = 20;
				}
				else if (Player.arms == BarbieArms)
				{
					bossHP = bossHP - 15;
					whatdamage = 15;
				}
				else if (Player.arms == ICArms)
				{
					bossHP = bossHP - 10;
					whatdamage = 10;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("공주님에게 %d의 피해를 입혔다!", whatdamage);
				Sleep(1500);
				gotoxy(10, 5);
				printf("             ");
				gotoxy(10, 5);
				printf("보스 HP : %d", bossHP);
				srand(time(NULL));
				whatattack = bossattack[rand() % 10];
				if (whatattack == 17)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 손목 때리기를 시전했다!");
					Sleep(1500);
					playerHP = playerHP - (5 + bosspower);
					whatdamage = (5 + bosspower);
				}
				else if (whatattack == 18)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 육두문자를 시전했다!");
					Sleep(1500);
					playerHP = playerHP - (3 + bosspower);
					whatdamage = (3 + bosspower);
				}
				else if (whatattack == 19)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 침 뱉기를 시전했다!");
					Sleep(1500);
					playerHP = playerHP - (10 + bosspower);
					whatdamage = (10 + bosspower);
				}
				else if (whatattack == 20)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 술주정을 시전했다!");
					Sleep(1500);
					whatdamage = 0;
					bosspower = bosspower + 2;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("도리베어는 %d의 피해를 입었다!", whatdamage);
				Sleep(1500);
				gotoxy(10, 10);
				printf("                 ");
				gotoxy(10, 10);
				printf("플레이어 HP : %d", playerHP);
			}  // 일반 공격


			else if (x == 115 && y == 50) { // 특수공격
				if (Player.arms == Wings)
				{
					if (wingsCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("도리베어는 회오오오리를 썻다!");
						Sleep(1500);
						bossHP = bossHP - 25;
						wingsCount--; // 횟수 세기
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("공주에게 25의 피해를 주었다!");
						Sleep(1500);
						gotoxy(x - 50, y);
						printf("공주는 풀이 죽어서 행동을 하지 못했다...");
						Sleep(1500);
						gotoxy(10, 5);
						printf("             ");
						gotoxy(10, 5);
						printf("보스 HP : %d", bossHP);
						gotoxy(x - 50, y);
						printf("                                         ");
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						if (bossHP <= 0 && wingsCount == 0)
						{
							Sleep(1500);
							PlaySound(NULL, 0, 0);
							system("cls");
							SPEnd04();
							break;
						}
					}
				}
				else if (Player.arms == CatArms)
				{
					if (catCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("도리베어는 냥냥펀치를 썻다!");
						Sleep(1500);
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("공주에게 40의 피해를 주었다!");
						Sleep(1500);
						bossHP = bossHP - 40;
						catCount--;
						gotoxy(10, 5);
						printf("             ");
						gotoxy(10, 5);
						printf("보스 HP : %d", bossHP);
						if (bossHP <= 0 && catCount == 0)
						{
							Sleep(1500);
							PlaySound(NULL, 0, 0);
							system("cls");
							SPEnd05();
							break;
						}
						srand(time(NULL));
						whatattack = bossattack[rand() % 10];
						if (whatattack == 17)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 손목 때리기를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (5 + bosspower);
							whatdamage = (5 + bosspower);
						}
						else if (whatattack == 18)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 육두문자를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (3 + bosspower);
							whatdamage = (3 + bosspower);
						}
						else if (whatattack == 19)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 침 뱉기를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (10 + bosspower);
							whatdamage = (10 + bosspower);
						}
						else if (whatattack == 20)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 술주정을 시전했다!");
							Sleep(1500);
							whatdamage = 0;
							bosspower = bosspower + 2;
							gotoxy(x - 50, y - 1);
							printf("                                         ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("공주님의 공격력이 2 상승했다!");
						}
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("도리베어는 %d의 피해를 입었다!", whatdamage);
						Sleep(1500);
						gotoxy(10, 10);
						printf("                 ");
						gotoxy(10, 10);
						printf("플레이어 HP : %d", playerHP);
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
					}
				}
				else if (Player.arms == ICArms) // 아이스크림 사용
				{
					if (icCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("도리베어는 자기 팔을 먹었다!");
						Sleep(1500);
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("피를 15 회복 했다!");
						Sleep(1500);
						icCount--;
						playerHP = playerHP + 15;
						if (playerHP >= 50)
						{
							playerHP = 50;
						}
						gotoxy(10, 10);
						printf("             ");
						gotoxy(10, 10);
						printf("플레이어 HP : %d", playerHP);
						srand(time(NULL));
						whatattack = bossattack[rand() % 10];
						if (whatattack == 17)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 손목 때리기를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (5 + bosspower);
							whatdamage = (5 + bosspower);
						}
						else if (whatattack == 18)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 육두문자를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (3 + bosspower);
							whatdamage = (3 + bosspower);
						}
						else if (whatattack == 19)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 침 뱉기를 시전했다!");
							Sleep(1500);
							playerHP = playerHP - (10 + bosspower);
							whatdamage = (10 + bosspower);
						}
						else if (whatattack == 20)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("공주가 술주정을 시전했다!");
							Sleep(1500);
							whatdamage = 0;
							bosspower = bosspower + 2;
						}
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("도리베어는 %d의 피해를 입었다!", whatdamage);
						Sleep(1500);
						gotoxy(10, 10);
						printf("                 ");
						gotoxy(10, 10);
						printf("플레이어 HP : %d", playerHP);
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
					}
				}
			}

			else if (x == 130 && y == 47) { // 방어하기
				gotoxy(x - 65, y + 3);
				printf("                                     ");
				gotoxy(x - 65, y + 1);
				printf("                                     ");
				gotoxy(x - 65, y + 2);
				printf("                                     ");
				gotoxy(x - 65, y + 1);
				printf("도리베어는 방어하기를 사용했다!");
				Sleep(1500);
				if (Player.passive == Listen)
				{
					if (whatlisten >= 7)
					{
						PlaySound(NULL, 0, 0);
						system("cls");
						TrueEnd08();
					}
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("%s", bossListen[whatlisten]);
					whatlisten++;
					Sleep(1500);
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("%s", bossListen[whatlisten]);
					whatlisten++;
					Sleep(1500);
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
				}
				else
				{
					srand(time(NULL));
					whatattack = bossattack[rand() % 10];
					if (whatattack == 17)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("공주가 손목 때리기를 시전했다!");
						Sleep(1500);
						playerHP = playerHP - (5 + bosspower) / 2;
						whatdamage = (5 + bosspower) / 2;
					}
					else if (whatattack == 18)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("공주가 육두문자를 시전했다!");
						Sleep(1500);
						playerHP = playerHP - (3 + bosspower) / 2;
						whatdamage = (3 + bosspower) / 2;
					}
					else if (whatattack == 19)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("공주가 침 뱉기를 시전했다!");
						Sleep(1500);
						playerHP = playerHP - (10 + bosspower) / 2;
						whatdamage = (10 + bosspower) / 2;
					}
					else if (whatattack == 20)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("공주가 술주정을 시전했다!");
						Sleep(1500);
						whatdamage = 0;
						bosspower = bosspower + 2;
					}
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("도리베어는 %d의 피해를 입었다!", whatdamage);
					Sleep(1500);
					gotoxy(10, 10);
					printf("                 ");
					gotoxy(10, 10);
					printf("플레이어 HP : %d", playerHP);
				}
			}

			else if (x == 130 && y == 50) { // 가방 보기
				gotoxy(65, 47);
				printf("                               ");
				gotoxy(65, 48);
				printf("                               ");
				gotoxy(65, 49);
				printf("                               ");
				gotoxy(65, 50);
				printf("                                          ");
				gotoxy(115, 47);
				printf("                                 ");
				gotoxy(115, 50);
				printf("                                ");
				x = 115, y = 47;
				gotoxy(x, y);
				printf("▶ %s", haveitem[0]);
				gotoxy(x - 50, y);
				printf("%s", itemeffect[0]);
				gotoxy(x, y + 1);
				printf("   %s", haveitem[1]);
				gotoxy(x, y + 2);
				printf("   %s", haveitem[2]);
				while (muham)
				{
					int n = keycontrol();
					switch (n) {
					case UP:
					{
						if (y > 47)
						{
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, y - 1);
							printf("▶");
							y = y - 1;
						}
						break;
					}
					case DOWN:
					{
						if (y < 49)
						{
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, y + 1);
							printf("▶");
							y = y + 1;
						}
						break;
					}
					case SUBMIT:
					{
						if (y == 47)
						{
							if (whatitemuse[0][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("껌을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("보호막 10을 얻었습니다!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("솜뭉치를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 10을 회복했습니다!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인싸토끼모자를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주의 공격력이 2 감소했습니다!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인피니티 건틀릿을 사용했습니다!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[0][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("매직서클을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주에게 50의 데미지를 입혔습니다!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("보스 HP : %d", bossHP);
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F맞은 성적표를 사용했습니다!");
								Sleep(1500);
								Freport();
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("아이스크림을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 15를 회복했습니다!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[0], "(사용함)");
								strcpy(itemeffect[0], "(사용함)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("어허!");
								Sleep(1500);
							}
						}
						else if (y == 48)
						{
							if (whatitemuse[1][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("껌을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("보호막 10을 얻었습니다!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("솜뭉치를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 10을 회복했습니다!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인싸토끼모자를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주의 공격력이 2 감소했습니다!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인피니티 건틀릿을 사용했습니다!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[1][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("매직서클을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주에게 50의 데미지를 입혔습니다!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("보스 HP : %d", bossHP);
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F맞은 성적표를 사용했습니다!");
								Sleep(1500);
								Freport();
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("아이스크림을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 15를 회복했습니다!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[1], "(사용함)");
								strcpy(itemeffect[1], "(사용함)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("어허!");
								Sleep(1500);
							}
						}
						else if (y == 49)
						{
							if (whatitemuse[2][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("껌을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("보호막 10을 얻었습니다!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[2], "(사용함)");
								strcpy(itemeffect[2], "(사용함)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("솜뭉치를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 10을 회복했습니다!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[2], "(사용함)");
								strcpy(itemeffect[2], "(사용함)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인싸토끼모자를 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주의 공격력이 2 감소했습니다!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[2], "(사용함)");
								strcpy(itemeffect[2], "(사용함)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("인피니티 건틀릿을 사용했습니다!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[2][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("매직서클을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("공주에게 50의 데미지를 입혔습니다!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("보스 HP : %d", bossHP);
								strcpy(haveitem[2], "(사용함)");
								strcpy(itemeffect[2], "(사용함)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F맞은 성적표를 사용했습니다!");
								Sleep(1500);
								Freport();
							}
							else if (whatitemuse[2][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("아이스크림을 사용했습니다!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("피 15를 회복했습니다!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("플레이어 HP : %d", playerHP);
								strcpy(haveitem[2], "(사용함)");
								strcpy(itemeffect[2], "(사용함)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("어허!");
								Sleep(1500);
							}
						}
						muham = 0;
					}
					}
					if (y == 47)
					{
						gotoxy(x - 50, 48);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("                                           ");
						gotoxy(x - 50, 47);
						printf("%s", itemeffect[0]);
					}
					else if (y == 48)
					{
						gotoxy(x - 50, 47);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("                                           ");
						gotoxy(x - 50, 48);
						printf("%s", itemeffect[1]);
					}
					else if (y == 49)
					{
						gotoxy(x - 50, 47);
						printf("                                           ");
						gotoxy(x - 50, 48);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("%s", itemeffect[2]);
					}
				}
				gotoxy(x - 50, 47);
				printf("                                           ");
				gotoxy(x - 50, 48);
				printf("                                           ");
				gotoxy(x - 50, 49);
				printf("                                           ");
				srand(time(NULL));
				whatattack = bossattack[rand() % 10];
				if (whatattack == 17)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 손목 때리기를 시전했다!");
					Sleep(1500);
					playerHP = playerHP - (5 + bosspower) / 2;
					whatdamage = (5 + bosspower) / 2;
				}
				else if (whatattack == 18)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 육두문자를 시전했다!");
					Sleep(1500);
					playerHP = playerHP + cheese - (3 + bosspower) / 2;
					whatdamage = (3 + bosspower) / 2;
				}
				else if (whatattack == 19)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 침 뱉기를 시전했다!");
					Sleep(1500);
					playerHP = playerHP + cheese - (10 + bosspower) / 2;
					whatdamage = (10 + bosspower) / 2;
				}
				else if (whatattack == 20)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("공주가 술주정을 시전했다!");
					Sleep(1500);
					whatdamage = 0;
					bosspower = bosspower + 2;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("도리베어는 %d의 피해를 입었다!", whatdamage);
				Sleep(1500);
				gotoxy(10, 10);
				printf("                 ");
				gotoxy(10, 10);
				printf("플레이어 HP : %d", playerHP);
				muham = 1;
				gotoxy(65, 47);
				printf("                               ");
				gotoxy(65, 48);
				printf("                                         ");
				gotoxy(65, 49);
				printf("                                          ");
				gotoxy(65, 50);
				printf("                                          ");
				gotoxy(115, 47);
				printf("                                 ");
				gotoxy(115, 48);
				printf("                                 ");
				gotoxy(115, 49);
				printf("                                 ");
				gotoxy(115, 50);
				printf("                                ");
				gotoxy(10, 5);
				printf("보스 HP : %d", bossHP);
				gotoxy(10, 10);
				printf("플레이어 HP : %d", playerHP);
				x = 115, y = 47;
				gotoxy(x, y);
				printf("▶ 기본공격");
				gotoxy(x - 50, y + 1);
				printf("공주에게 기본 공격을 가한다!");
				gotoxy(x, y + 3);
				printf("   특수공격");
				gotoxy(x + 15, y);
				printf("   방어하기");
				gotoxy(x + 15, y + 3);
				printf("   가방보기");
			}
		}
		}
		if (x == 115 && y == 47)
		{
			gotoxy(x - 50, y + 3);
			printf("                                     ");
			gotoxy(x - 50, y + 1);
			printf("                                     ");
			gotoxy(x - 50, y + 2);
			printf("                                     ");
			gotoxy(x - 50, y + 1);
			printf("공주에게 기본 공격을 가한다!");
		}
		else if (x == 130 && y == 47)
		{
			gotoxy(x - 65, y + 3);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("공주가 주는 피해를 방어한다!");
		}
		else if (x == 115 && y == 50)
		{
			gotoxy(x - 50, y - 1);
			printf("                                        ");
			gotoxy(x - 50, y);
			printf("                                        ");
			gotoxy(x - 50, y + 1);
			printf("                                        ");
			gotoxy(x - 50, y + 2);
			printf("                                        ");
			gotoxy(x - 50, y - 2);
			printf("공주에게 특수 피해를 가한다!      ");
			if (Player.arms == Wings)
			{
				if (wingsCount > 0)
				{
					gotoxy(x - 50, y);
					printf("회오오오오리를 사용할 수 있다 (%d번)", wingsCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("다 사용했어요.");
				}
			}
			else if (Player.arms == CatArms)
			{
				if (catCount > 0)
				{
					gotoxy(x - 50, y);
					printf("냥냥펀치를 사용할 수 있다 (%d번)", catCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("다 사용했어요.");
				}
			}
			else if (Player.arms == ICArms)
			{
				if (icCount > 0)
				{
					gotoxy(x - 50, y);
					printf("팔을 먹을 수 있다 (%d번)", icCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("다 사용했어요.");
				}
			}
			else
			{
				gotoxy(x - 50, y);
				printf("아무것도 없다...");
			}
		}
		else if (x == 130 && y == 50)
		{
			gotoxy(x - 65, y);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y - 2);
			printf("가방을 열어 아이템을 사용한다!");
			gotoxy(x - 65, y);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y - 1);
			printf("보유 아이템");
			gotoxy(x - 65, y);
			printf("%-10s", haveitem[0]);
			gotoxy(x - 55, y);
			printf("%-10s", haveitem[1]);
			gotoxy(x - 42, y);
			printf("%-10s", haveitem[2]);

		}

		if (bossHP <= 0)
		{
			Sleep(1500);
			system("cls");
			if (Player.arms == DoriArms)
			{
				PlaySound(NULL, 0, 0);
				SPEnd06();
			}
			PlaySound(NULL, 0, 0);
			NorEnd09();
		}
		if (playerHP + cheese <= 0)
		{
			Sleep(3000);
			system("cls");
			if (Player.passive == DeadHard)
			{
				PlaySound(NULL, 0, 0);
				SPEnd03();
			}
			PlaySound(NULL, 0, 0);
			BadEnd02();
		}

	}
}

int pot() // 오브젝트 목록 : 항아리 --------------------------------------------------
{
	system("cls");
	gotoxy(65, 25);
	printf("항아리 여는중.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	printf("항아리 여는중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("항아리 여는중...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	printf("항아리 여는중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("항아리 여는중..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = potitems[rand() % 10];
	if (whatitem == 0)
	{
		printf("솜뭉치를 얻었습니다.");
		strcat(Player.items, "Som");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 1)
	{
		printf("껌을 얻었습니다.");
		strcat(Player.items, "Gum");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 2)
	{
		printf("꽝임 ㅋ");
	}

}
int box() // 오브젝트 목록 : 상자
{
	system("cls");
	gotoxy(65, 25);
	printf("상자 여는중.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("상자 여는중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("상자 여는중...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("상자 여는중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("상자 여는중..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = boxitems[rand() % 10];
	if (whatitem == 0)
	{
		printf("솜뭉치를 얻었습니다.");
		strcat(Player.items, "Som");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 1)
	{
		printf("껌을 얻었습니다.");
		strcat(Player.items, "Gum");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 2)
	{
		printf("꽝임 ㅋ");
	}
	else if (whatitem == 3)
	{
		printf("인싸토끼를 얻었습니다.");
		strcat(Player.items, "Inssa");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 4)
	{
		printf("WoW !!!! 인피니티 건틀릿을 얻었습니다.");
		strcat(Player.items, "Infinity");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}

}
int hole() // 오브젝트 목록 : 구덩이
{
	system("cls");
	gotoxy(65, 25);
	printf("구덩이 파보는중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("구덩이 파보는중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("구덩이 파보는중...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("구덩이 파보는중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("구덩이 파보는중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("낫띵 이스 해브.....☆");
}

int bookshelf() // 오브젝트 목록 : 책장
{
	system("cls");
	gotoxy(65, 25);
	printf("책을 꺼내는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("책을 꺼내는 중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("책을 꺼내는 중...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("책을 꺼내는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("책을 꺼내는 중..");
	Sleep(1000);
	srand(time(NULL));
	whatitem = bookitems[rand() % 10];

	if (whatitem == 9) // 수학의 정석
	{
		system("cls");
		gotoxy(65, 25);
		printf("수학의 정석이라는 책이다.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("보기만 해도 기분 나쁘니 그냥 가자.");
	}
	else if (whatitem == 10) // TAGD
	{
		system("cls");
		gotoxy(65, 25);
		printf("The Art Of Game Design 이라는 책이다..");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("라면 받침으로 좋을 것 같다.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("이 하수구를 나가는 데 필요는 없을 것 같다.");
	}
	else if (whatitem == 11) // 농사의 정석, C뿌리기 획득
	{
		system("cls");
		gotoxy(65, 25);
		printf("농사의 정석이라는 책이다.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("'교수님의'C뿌리기에 대한 설명이 나와있다.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("책을 읽고 C뿌리기를 배웠다!");
		Player.passive = DropC;
	}
}

int mousehole() // 오브젝트 목록 : 쥐구멍
{
	srand(time(NULL));
	whatitem = mouseitems[rand() % 10];
	char a[] = "언젠가 쥐가 구멍을 빠져나와 치즈를 가져갈 것을 알기에,,";
	char b[] = "의지가 차오른다.";
	if (whatitem == 2)
	{
		system("cls");
		gotoxy(65, 25);
		printf("그저 쥐구멍인가 보다.");
	}

	else if (whatitem == 8)
	{
		system("cls");
		for (int i = 0; i < strlen(a); i++)
		{
			gotoxy((i * 2) + 20, 25);
			printf("%c", a[i]);
			Sleep(200);
		}
		for (int i = 0; i < strlen(b); i++)
		{
			gotoxy((i * 2) + 57, 27);
			printf("%c", b[i]);
			Sleep(200);
		}
		cheese = cheese + 10;
	}
}

int circle() // 오브젝트 목록 : 이상한 원
{
	system("cls");
	gotoxy(65, 25);
	printf("이상한 원 탐색중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("이상한 원 탐색중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("이상한 원 탐색중...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("이상한 원 탐색중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("이상한 원 탐색중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = circleitems[rand() % 10];

	if (whatitem == 2)
	{
		printf("아무일도.. 없었다..");
	}
	else if (whatitem == 5)
	{
		printf("아니 이것은....?");
		Sleep(1000);
		system("cls");
		gotoxy(65, 25);
		printf("Magic Circle을 획득하였습니다!!");
		strcat(Player.items, "MagicCircle");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}

}

int button() // 오브젝트 목록 : 스위치
{
	system("cls");
	gotoxy(65, 25);
	printf("스위치를.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("스위치를 눌.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("스위치를 눌러.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("스위치를 눌러보.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("스위치를 눌러보자..");
	Sleep(1000);
	srand(time(NULL));
	whatitem = buttonitems[rand() % 10];

	if (whatitem == 2)
	{
		system("cls");
		gotoxy(65, 25);
		printf("눌러봐도 아무 일도 없었다.");
	}
	else if (whatitem == 7)
	{
		system("cls");
		gotoxy(2, 2);
		printf("(쿠궁...)");
		Sleep(1000);
		system("cls");
		gotoxy(20, 10);
		printf("(쿠궁......)");
		Sleep(1000);
		system("cls");
		gotoxy(40, 20);
		printf("(콰광.........)");
		Sleep(2000);
		system("cls");
		gotoxy(65, 25);
		printf("어디서 물소리가 들리는데...?");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("(쿠곽ㄱ가ㅘㅗ아ㅗ가과왕아)");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("으으으ㅔㅇ에ㅔㄱ!!!! 도 망 쳐 !!!!!!!!!!!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("도리베어는 죽기살기로 통로를 탈출했다!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("도리베어는 죽기살기를 얻었다!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("도리베어는 그렇게 어느 통로에 도착하게 되는데...");
		Sleep(3000);
		srand(time(NULL));
		whatitem = buttongo[rand() % 3];
		Player.passive = DeadHard;
		if (whatitem == 14)
		{
			nRoomC1();
		}
		else if (whatitem == 15)
		{
			nRoomC2();
		}
		else if (whatitem == 16)
		{
			nRoomC3();
		}
	}
}
int paper() // 오브젝트 목록 : 종이조각
{
	system("cls");
	gotoxy(65, 25);
	printf("종이조각 맞춰보는 중.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("종이조각 맞춰보는 중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("종이조각 맞춰보는 중...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("종이조각 맞춰보는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("종이조각 맞춰보는 중..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = paperitems[rand() % 10];

	if (whatitem == 2)
	{
		printf("맞춰보니.. 청구서였다고한다..");
	}
	else if (whatitem == 6)
	{
		printf("어라....? F맞은 성적표인가...?");
		Sleep(1000);
		system("cls");
		gotoxy(65, 25);
		printf("F 맞은 성적표를 얻었습니다.");
		strcat(Player.items, "Freport");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
}

int stranger() // 오브젝트 목록 : 정체를 알 수 없는 사람
{
	system("cls");
	srand(time(NULL));
	whatitem = npcitems[rand() % 10];

	if (whatitem == 12) // 아이스크림 상인
	{
		gotoxy(55, 25);
		printf("아이스크림 사세요!!! 단 돈 20골드!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("돈이 없다고요??? 그럼 그냥 드릴게요!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("아이스크림을 얻었습니다!!! 야호!!!");
		strcat(Player.items, "IceCream");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 13) // 노숙자
	{
		gotoxy(65, 25);
		printf("자고 있는 노숙자다.");
	}
}

int Gstranger() // 오브젝트 목록 : G417 전용 정체를 알 수 없는 사람, ???이자 박실러
{
	system("cls");
	gotoxy(55, 25);
	printf("??? : 으윽....");
	Sleep(3000);
	system("cls");
	gotoxy(55, 25);
	printf("이상한 사람인 것 같다.");
	Sleep(3000);
	gotoxy(55, 30);
	printf("▶ 말을 건다");
	gotoxy(55, 31);
	printf("   기분 나쁘니 그냥 가자");
	x = 55, y = 30;
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 30) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, --y);
				printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 31) {
				gotoxy(x, y);
				printf("   ");
				gotoxy(x, ++y);
				printf("▶");
			}
			break;
		}
		case SUBMIT: {
			if (y == 30) {
				system("cls");
				gotoxy(55, 25);
				printf("??? : 으,,어어,,,어");
				Sleep(3000);
				gotoxy(55, 30);
				printf("▶ 말을 계속 걸어본다");
				gotoxy(55, 31);
				printf("   어딘가 모자른 사람 같다. 그냥 가자");
				x = 55, y = 30;
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 30) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, --y);
							printf("▶");
						}
						break;
					}
					case DOWN: {
						if (y < 31) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, ++y);
							printf("▶");
						}
						break;
					}
					case SUBMIT: {
						if (y == 30) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
							system("cls");
							gotoxy(55, 25);
							printf("??? : 공주가,, 화가 나있어,,");
							Sleep(3000);
							gotoxy(55, 30);
							printf("▶ 무슨 일인지 자세히 물어보자");
							x = 55, y = 30;
							while (1) {
								int n = keycontrol();
								switch (n) {
								case SUBMIT: {
									if (y == 30) {
										system("cls");
										gotoxy(55, 25);
										printf("??? : 공주님이 무슨 일인지 화가 잔뜩 나있어..");
										Sleep(3000);
										gotoxy(55, 27);
										printf("      화를 주체하지 못하고 지하실에서 울분을 토하고 있지...");
										Sleep(3000);
										gotoxy(55, 29);
										printf("도리베어 : 어떻게 하면 진정시키죠?");
										Sleep(3000);
										system("cls");
										gotoxy(55, 25);
										printf("??? : 나의 사부님이 항상 말하셨지...");
										Sleep(3000);
										gotoxy(55, 27);
										printf("      안생에서 가장 중요한 것은 '경청하기'라고...");
										Sleep(3000);
										gotoxy(55, 29);
										printf("      그녀를 공격하지 말고 귀를 기울여줘....");
										Sleep(3000);
										gotoxy(55, 31);
										printf("	  '방어하기'를 하다 보면 괜찮아질지도.....");
										Sleep(3000);
										system("cls");
										gotoxy(55, 25);
										printf("경청하기를 배웠다.");
										Sleep(3000);
										Player.passive = Listen;

										system("cls");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                       :77vvvvL77i.                                                                 |\n");
										printf("                                                                    iUYi.       .:7us:                                                              |\n");
										printf("                                                                  rXr                rSv                                                            |\n");
										printf("                                                                 q7                    iK7                                                          |\n");
										printf("                                                               .d.                       LP                                                         |\n");
										printf("                                                              :d                          .g.                                                       |\n");
										printf("                                                             .Z                             R.                                                      |\n");
										printf("                                                             M                        .      Q                                                      |\n");
										printf("                                                            D.       .                .Ir    .D                                                     |\n");
										printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
										printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
										printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
										printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
										printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
										printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
										printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
										printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
										printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
										printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
										printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
										printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
										printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
										printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
										printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
										printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
										printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
										printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
										printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
										printf("           g                                                        1U7B           .B                                                     :X        |\n");
										printf("           7s                                                        uB             :B      BB                                            P.        |\n");
										printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
										printf("             g                                                     BP                B                                                   Y7         |\n");
										printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
										printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
										printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
										printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
										printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
										printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
										printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
										printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
										printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
										printf(" :U7                                                                    Bi          B                                                             YL|\n");
										printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
										x = 0, y = 50;
										gotoxy(x, y);
										printf("▶ 왼쪽 길");
										gotoxy(x, y + 1);
										printf("   가운데 길");
										gotoxy(x, y + 2);
										printf("   오른쪽 길");
										while (1) {
											int n = keycontrol();
											switch (n) {
											case UP: {
												if (y > 50) {
													gotoxy(x, y);
													printf("   ");
													gotoxy(x, --y);
													printf("▶");
												}
												break;
											}
											case DOWN: {
												if (y < 52) {
													gotoxy(x, y);
													printf("   ");
													gotoxy(x, ++y);
													printf("▶");
												}
												break;
											}
											case SUBMIT: {
												if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
													gRoomC1();
												}
												else if (y == 51) {
													gRoomC2();
													break;
												}
												else if (y == 52) {
													gRoomC3();
												}
											}
											}
										}
									}
								}
								}
							}
						}
						else if (y == 31) {
							system("cls");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                       :77vvvvL77i.                                                                 |\n");
							printf("                                                                    iUYi.       .:7us:                                                              |\n");
							printf("                                                                  rXr                rSv                                                            |\n");
							printf("                                                                 q7                    iK7                                                          |\n");
							printf("                                                               .d.                       LP                                                         |\n");
							printf("                                                              :d                          .g.                                                       |\n");
							printf("                                                             .Z                             R.                                                      |\n");
							printf("                                                             M                        .      Q                                                      |\n");
							printf("                                                            D.       .                .Ir    .D                                                     |\n");
							printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
							printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
							printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
							printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
							printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
							printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
							printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
							printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
							printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
							printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
							printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
							printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
							printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
							printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
							printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
							printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
							printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
							printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
							printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
							printf("           g                                                        1U7B           .B                                                     :X        |\n");
							printf("           7s                                                        uB             :B      BB                                            P.        |\n");
							printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
							printf("             g                                                     BP                B                                                   Y7         |\n");
							printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
							printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
							printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
							printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
							printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
							printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
							printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
							printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
							printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
							printf(" :U7                                                                    Bi          B                                                             YL|\n");
							printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
							x = 0, y = 50;
							gotoxy(x, y);
							printf("▶ 왼쪽 길");
							gotoxy(x, y + 1);
							printf("   가운데 길");
							gotoxy(x, y + 2);
							printf("   오른쪽 길");
							while (1) {
								int n = keycontrol();
								switch (n) {
								case UP: {
									if (y > 50) {
										gotoxy(x, y);
										printf("   ");
										gotoxy(x, --y);
										printf("▶");
									}
									break;
								}
								case DOWN: {
									if (y < 52) {
										gotoxy(x, y);
										printf("   ");
										gotoxy(x, ++y);
										printf("▶");
									}
									break;
								}
								case SUBMIT: {
									if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
										gRoomC1();
									}
									else if (y == 51) {
										gRoomC2();
										break;
									}
									else if (y == 52) {
										gRoomC3();
									}
								}
								}
							}
						}
					}
					}
				}
			}
			else if (y == 31) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("▶ 왼쪽 길");
				gotoxy(x, y + 1);
				printf("   가운데 길");
				gotoxy(x, y + 2);
				printf("   오른쪽 길");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, --y);
							printf("▶");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf("   ");
							gotoxy(x, ++y);
							printf("▶");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // 여기서 값을 넣어주고 그 값을 main함수로 보내주고 그 값에 따라 main함수에서 방으로 이동시켜야 함.
							gRoomC1();
						}
						else if (y == 51) {
							gRoomC2();
							break;
						}
						else if (y == 52) {
							gRoomC3();
						}
					}
					}
				}

			}
		}
		}
	}

}
int pipe() // 오브젝트 목록 : 파이프
{
	system("cls");
	gotoxy(65, 25);
	printf("파이프 안을 뒤져보는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("파이프 안을 뒤져보는 중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("파이프 안을 뒤져보는 중...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("파이프 안을 뒤져보는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("파이프 안을 뒤져보는 중..");
	Sleep(1000);
	system("cls");

	if (room == 1) // c많은 하수구
	{
		gotoxy(55, 25);
		printf("파이프 안에서 앵무새 날개를 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("앵무새 날개를 도리베어의 팔에 부착하였다!!");
		Sleep(1000);
		Player.arms = Wings;
	}

	else if (room == 2) // G417 하수구
	{
		gotoxy(55, 25);
		printf("파이프 안에서 고양이 팔을 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("고양이 팔을 내 팔에 부착하였다!!");
		Sleep(1000);
		Player.arms = CatArms;
	}

	else if (room == 3) // 평범한 하수구
	{
		gotoxy(55, 25);
		printf("파이프 안에서 도리베어의 팔을 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("(띠요옹?!?! 이것은 내 팔이잖어?!?!)");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("도리베어의 팔을 부착하였다!");
		Sleep(1000);
		Player.arms - DoriArms;
	}

}

int lake() // 오브젝트 목록 : 고인 물
{
	system("cls");
	gotoxy(65, 25);
	printf("고인물 안을 뒤져보는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("고인물 안을 뒤져보는 중..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("고인물 안을 뒤져보는 중...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("고인물 안을 뒤져보는 중.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("고인물 안을 뒤져보는 중..");
	Sleep(1000);
	system("cls");

	if (room == 1) // c많은 하수구
	{
		gotoxy(55, 25);
		printf("고인 물 안에서 나뭇가지를 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("나뭇가지를 도리베어의 팔에 부착하였다!!");
		Sleep(1000);
		Player.arms = Twigs;
	}

	else if (room == 2) // G417 하수구
	{
		gotoxy(55, 25);
		printf("고인 물 안에서 바비인형의 팔을 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("바비인형의 팔을 내 팔에 부착하였다!!");
		Sleep(1000);
		Player.arms = BarbieArms;
	}

	else if (room == 3) // 평범한 하수구
	{
		gotoxy(55, 25);
		printf("고인 물 안에서 아이스크림 팔을 발견했다!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("(띠요옹..? 고인 물 안에 아이스크림이..?)");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("아이스크림 팔을 부착하였다!");
		Sleep(1000);
		Player.arms = ICArms;
	}
}

int BadEnd01() // 엔딩 정리 : 팔 x 엔딩 -----------------------------------------------------
{
	system("cls");
	gotoxy(10, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("난.. 공주님과 맞서 싸울 수 있을까...?");
	Sleep(3000);
	gotoxy(10, 8);
	printf("이 꼴로 간다면.. ");
	Sleep(1500);
	gotoxy(10, 11);
	printf("팔 없이 간다면.. 난 절대 해내지 못할거야..");
	Sleep(3000);
	gotoxy(10, 14);
	printf("다시 처음부터 돌아가서 해보는 거야..!");
	Sleep(3000);
	system("cls");
	gotoxy(65, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("그렇게 도리베어는");
	Sleep(3000);
	gotoxy(62, 23);
	printf("공주님을 만나지 못하고");
	Sleep(3000);
	gotoxy(64, 26);
	printf("팔을 가지지 못한 채");
	Sleep(3000);
	gotoxy(57, 29);
	printf("쓸쓸히 하수구 안으로 걸어갔답니다");
	Sleep(3000);
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                               i                                                                    |\n");
	printf("                                                                 irvuukssvriBUirvvJukuuvi                                                           |\n");
	printf("                                                             ruKkLii        D          irjSqJi                                                      |\n");
	printf("                                                         ikPIri             Ri              ivqPj                                                   |\n");
	printf("                                                      iXbui                 Mi                  iqZj                                                |\n");
	printf("                                                    YZSi                    gi                     rEZr                                             |\n");
	printf("                                                  Vgv                       Er                        VQv                                           |\n");
	printf("                                                qMr                         Er                          IBY                                         |\n");
	printf("                                              uBr                           Kv                            VBi                                       |\n");
	printf("                                            iBu                             Kv                              RQ                                      |\n");
	printf("                                           ZQ                               VJ                               rBv                                    |\n");
	printf("                                          Bv                                VJ                                 QB                                   |\n");
	printf("                                        vB                                  uI                                  YB                                  |\n");
	printf("                                       qB                                   uk                                   iBi                                |\n");
	printf("                                      Rg                                    LK                                     Bv                               |\n");
	printf("                                     QP                                     LX                                      Bv                              |\n");
	printf("                                    Qb                                      vb                                       Br                             |\n");
	printf("                                   PR                                       vd                                        Bi                            |\n");
	printf("                                  vB                                        rg                                         B                            |\n");
	printf("                                  B                                         iD                                         rB                           |\n");
	printf("                                 Bi                                         iR                                          Qb                          |\n");
	printf("                                qD                                          iQ                                           B                          |\n");
	printf("                                Q                                           iQ                                           iQ                         |\n");
	printf("                               Bv                                           iB                                            Bi                        |\n");
	printf("                               B                                             B                                             B                        |\n");
	printf("                              Bv                                             B                                             Bi                       |\n");
	printf("                              B                                              B                                             rB                       |\n");
	printf("                             sQ                     iiiiiii   rkujbr         B                                              B                       |\n");
	printf("                             Bi              LqvrUBPriivrvvuuBQ    BL        B                                              Qu                      |\n");
	printf("                             B              SQ   Bb           iDZ  BY        B                                              rB                      |\n");
	printf("                            iB               EJ Mg              iBQP         B                                               B                      |\n");
	printf("                            SP                IBS                 B          Q                                               B                      |\n");
	printf("                            Qv              iBv                   B          B                                               Bi                     |\n");
	printf("                            Bi              Bi      ㅡ   ㅠ      PB   iPugi  B    BSiXB                                      Qj                     |\n");
	printf("                            B               rBr       ㅡ      iZQL    Bi BQ  B   iB  EB                                      EK                     |\n");
	printf("                            B                 IDXvi     iirvSSvrB     iLJL   B    irvi                                       SZ                     |\n");
	printf("                            B                    irvuBrvvii      B           B                                               qd                     |\n");
	printf("                            B                        B           BV          B                                               dK                     |\n");
	printf("                            Bi                      iB            B          B                                               Bs                     |\n");
	printf("                            Qv                      UQ            B          B                                               Bi                     |\n");
	printf("                            UE                      uB            B          B                                               B                      |\n");
	printf("                            iB                       B          iBi          B                                               B                      |\n");
	printf("                             B                       iBJ     irBB            B                                               B                      |\n");
	printf("                             Bi                        BivBiXB  B            B                                               B                      |\n");
	printf("                             VB                        B  Q  B  B            B                                               B                      |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(110, 50);
	printf("Bad Ending_#01");
	Sleep(1500);
	gotoxy(110, 51);
	printf("도리베어는 너무 두려웠어");
	Sleep(3000);
	system("cls");
	exit(0);
}

int BadEnd02() // 엔딩 정리 : 보스전에서 도리베어가 지는 엔딩
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 도리베어가");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" 마지막 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("에 맞았어요!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 쓰러지고, ");
	Sleep(1000);
	printf("전의를 상실하였어요.");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("공주 : 이 팔은 도대체 어디서 구해온거람;;");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("공주 : 다신 오지 못하게 해주마!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("도리베어 : 끄아아아ㅏㅇ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 도리베어의 팔은 나가 떨어지게 되었어요! ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그리고 팔과 함께 도리베어는 하수구로 떨어지게 되었어요. ");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 ");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("어두컴컴한 하수구에서 방황하게 되었답니다.");
	Sleep(2000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                         rr                                                                         |\n");
	printf("                                                                        QiiB                                                                        |\n");
	printf("                                                                iiiiii UU   B                                                                       |\n");
	printf("                                                       ivi   vPPjvrvrvvVbI  B             B                                                         |\n");
	printf("                                                      gJivkLvL            VQr             BI                                                        |\n");
	printf("                                                     Ss   Q                iR          bgYiii                                                       |\n");
	printf("                                                     iR  Yu         i  d    iB          g    g                                                      |\n");
	printf("                                                      iXiB i P       XX      iB         YL   Xk                                                     |\n");
	printf("                                                        B   Zb        BU      vd         Q    Zv                                                    |\n");
	printf("                                                       Bi   B L       i Q      B         rj    Rr                                                   |\n");
	printf("                                                      Bi   iv  r         Y     di         Q     Bi                                                  |\n");
	printf("                                                     vP                        B          Pi     Bi                                                 |\n");
	printf("                                                     gi           ▽          Ib           Q      Qv                                                |\n");
	printf("                                                     JV            i        rqv            bi      bU                                               |\n");
	printf("                                                      Bi                iYEBPi              B       IK                                              |\n");
	printf("                                                       QI            udEui iivBQ            iR       Ks                                             |\n");
	printf("                                                        rPqJvvvLUkSQBs        iBY            II       B                                             |\n");
	printf("                                                           iiiii    Br          ug            Pu      B                                             |\n");
	printf("                                                                     IB           VX           kd    II                                             |\n");
	printf("                                                                      vX          gQbi          iXVUKj                                              |\n");
	printf("                                                                       B         BE                                                                 |\n");
	printf("                                                                       B        Lk     g                                                            |\n");
	printf("                                         iiii           Vbi            iM        bi  uUjb                                                           |\n");
	printf("                                      ISYvrvvsuVkLi   ugi Q             Qi        SVYB  Vv                                                          |\n");
	printf("                                     Mj          irvkQY  KJ              B          r    Biii                                                       |\n");
	printf("                                      Mi                  BE              Bi            BqiijQ                                                      |\n");
	printf("                                       uEvi           iivrBB               QJ        iPUQ     B                                                     |\n");
	printf("                                         ivJuIUIUIuuJYvii                   JMv   vdkv   Q    iB                                                    |\n");
	printf("                                                                              rrbkiB     uI    vM                                                   |\n");
	printf("                                                                                g  uv     gv    rRv                                                 |\n");
	printf("                                                                               B   uv      RY     vJkIVi                                            |\n");
	printf("                                                                              gr   Pi       qb         bY                                           |\n");
	printf("                                                                             vb    R         iQv        B                                           |\n");
	printf("                                                                             B     B           vbVi   rQi                                           |\n");
	printf("                                                                 ii         gi    vq              vuUuv                                             |\n");
	printf("                                                               iQrvUIILri   g     B                                                                 |\n");
	printf("                                                               iQ     irsuuDM    sX                                                                 |\n");
	printf("                                                                SX          i    B                                                                  |\n");
	printf("                                                                 YMr            B                                                                   |\n");
	printf("                                                                   sbXvi      vB                                                                    |\n");
	printf("                                                                      rJSSSkVPu                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#02");
	Sleep(1500);
	gotoxy(110, 51);
	printf("도리베어는 결국 해내지 못했어");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd03() // 죽기살기 패시브를 가진 상태에서 보스전에서 도리베어의 HP가 0으로 떨어졌을 때
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 공주가");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" 마지막 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 가했어요!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("(안돼..! 이대로 죽지않아!!)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 도리베어가 죽기살기로 뛰어서 ");
	Sleep(1000);
	printf("공주의 일격을 회피했어요!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("공주 : 뭣이??!! 이걸 피한단 말이여?!!?");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("도리베어 : (사.. 살았다... 이 곳을 탈출해야해!)");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 위기를 모면한 도리베어는 살기 위해 공주의 집에서 도망쳤어요!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("도리베어 : 저 지옥같은 곳은 내겐 너무 가혹한 곳인 것 같아!");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("           다른 곳에서 지내는 것이 나을 것 같다.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 외딴 안전한 곳에서 잘 먹고 잘 살게 되었답니다.");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                     irri                                                                           |\n");
	printf("                                                  irii             vUr  iE                                                                          |\n");
	printf("                                                uJi  vS  iriivBii vi     rU                                                                         |\n");
	printf("                                               K   irvPviii  M kDSI      di                                                                         |\n");
	printf("                                              S ruvi           u YiLB   Vv                                                                          |\n");
	printf("                                             vQQv               is siBiki                                                                           |\n");
	printf("                                             QQ                 i  ii gS                                                                            |\n");
	printf("                                             g                        iVU j                                                                         |\n");
	printf("                                            jr               i         YVii                                                                         |\n");
	printf("                                            Z              rBB          gY XY                                                                       |\n");
	printf("                                            M             iBq           Eiiki   iii                                                                 |\n");
	printf("                                            D                           Pivi  ivii   ii  ii ii                                                      |\n");
	printf("                                            Q     MQBBP   iB             qii iriii vqUvvJu  ii ir                                                   |\n");
	printf("                                           vU            jsb            Z  LvYDYEr   vP iVi  i                                                      |\n");
	printf("                                          Lq            Bvis           viiZvi    LikZ     Sv  ii                                                    |\n");
	printf("                                         Vv                            BvY                 M                                             i          |\n");
	printf("                                         M                            BI        irvvvvY    Vr                                          rK   ii      |\n");
	printf("                                         R                          rBs    irkPSi     ibvirP                                         iXv  ii        |\n");
	printf("                                          R                       sViuusQSr ii    i     iii                                         Jv   ri         |\n");
	printf("                                           Pv                  vkui      KjI    ii                                                jDi  Ir           |\n");
	printf("                                            iIji           irgui        Pi    i  Xq                                             rBK  jP             |\n");
	printf("                                               ivYYLvrivQgvi b          Zg uB Yvv  V     i                                     BB  iMr              |\n");
	printf("                                                      vSi    Q            vi   iB  V    vi i         i                      iXBi  Zq                |\n");
	printf("                                         iii       ivji     rBi                  qX    viiVi    i  rr  iv  i             iiLQS  uBi ii              |\n");
	printf("                                      qiiiiirrvvvvri       qi M                  uK   iivk    ii  r   vi  vi           iSvSBi iBV  i                |\n");
	printf("                                      Di                 UV    Q   S              k   ii    iDv ij       v            kPrDZ  ZQ  r                  |\n");
	printf("                                       JUi            ruUi     id U usi          iJ iIsLrvvvviiiiirvJv      ii      igIVBL iBv Yk                   |\n");
	printf("                                         ivYLYvvvLvsvvi         YZ   Bs          QVvri                di   ii      ZQPQBi qEiKBi                    |\n");
	printf("                                                                      gr        vY      iivvYvLvi      R         vBBBBX sQuUBP                      |\n");
	printf("                                                                    Pvr        iQ  ivsvri       idi    ki       QBBBZivBRsBB                        |\n");
	printf("                                                                  BuVr        rKiiii              Kj   g      vBBQBuiPBXVBP                         |\n");
	printf("                                                                   D         Uu                    vXius     QQBBBvvQBJQBi                          |\n");
	printf("                                                                    Pr    iPZ   vr                   i     iBgZQZvPBgJBP                            |\n");
	printf("                                                                     irvrVQiLi ki  ii                     kBugBuLBBkPBi                             |\n");
	printf("                                                                         S   DJ   vvi                    ZgLQBsSBMuBD                               |\n");
	printf("                                                                         D    E  vvi                   igVJBMLDBXdBi                                |\n");
	printf("                                                                         D    Uiiiiir                 vdJUBdLQBuBE                                  |\n");
	printf("                                                                         D    iP  is                 uPvSBUYZKqBi                                   |\n");
	printf("                                                                         P    iu  V                iYkrXBivLvQB                                     |\n");
	printf("                                                                         P    iY uii              ivviUX rijQu                                      |\n");
	printf("                                                                         D    viirv              riiiYv i gQi                                       |\n");
	printf("                                                                         D    KiiI              i   ri i JI                                         |\n");
	printf("                                                                        R    iK S                     i ii                                          |\n");
	printf("                                                                       Xi    R i                                                                    |\n");
	printf("                                                                      iR   vP                                                                       |\n");
	printf("                                                                       irvri                                                                        |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#03");
	Sleep(1500);
	gotoxy(110, 51);
	printf("하지만 도리베어는 절대 포기하지 않아");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd04() // 엔딩 정리 : 앵무새 날개를 가진 상테에서 고유 스킬 3번 사용, 마무리 일격
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 도리베어가 ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" 회오오오리");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("로 ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("마무리 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 가했어요!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("도리베어 : 끝이다!! 회오오오오리!!!");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("공주 : 으 으 으악!!!!!!!!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 공주는 그대로 회오리를 타고 하늘로 날아 올라갔어요!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("공주 : 두고..!!! 보...!! ㅈ..ㅏ..!");
	Sleep(1000);
	printf("(피슝-☆)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 공주는 그렇게 하늘 위 어딘가로 슈웅 날라갔어요!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("도리베어 : 헤헤 이 날개도 꽤 쓸모가 있구먼 ㅎㅎ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 공주네 집에서");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         자유로이 날아다닐 수 있게 되었답니다!");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                               VISv                                 |\n");
	printf("                                                                                                              Q   YB                                |\n");
	printf("                                                                                                          irvBPrri Qv            kqdv               |\n");
	printf("                                                                                                 XKKv  uDPuri   ivKBE          YBr  Bi              |\n");
	printf("                                                                                               iBi  uBPr            iBr       Qb    Ps              |\n");
	printf("                                                                                               B    gi        /       BL     Br     BB              |\n");
	printf("                                                                                               MS  Vr                  Bi  iB      i rD             |\n");
	printf("                                                                                                KDvQv  ㅡ               B iB         iB             |\n");
	printf("                                                                                                   rM     Ivr           QiB     Qi   PU             |\n");
	printf("                                                                                                    B    g   iR         BQ      Bi   B              |\n");
	printf("                                                                                                   iR    P   vBr       BQ      iQ   iB              |\n");
	printf("                                                                                                   Rr    B iB  P     rBQB      Qv   iB              |\n");
	printf("                                                                                                   B      BY  i    iQd   Sgv   i    Bi              |\n");
	printf("                                                                                                   YB            sQK       XB      gZ               |\n");
	printf("                                              iuSUJUujsJsjYjJuuIUXSq                                ikUSkIsvvgBBBi          rB    BP                |\n");
	printf("                                           uQRVi                                                           vdIi g            Sq iBv                 |\n");
	printf("                                        LBBs                                                            LEVi    Mi            Q s                   |\n");
	printf("                                      ZBK                  iLuPdgZMgDbSr                             LgPr       SY            B                     |\n");
	printf("                                   iQBv             ivUEgQEXvii       iVBQ                        idZv          iR            B                     |\n");
	printf("                                  BBr         ijgQRbSvi                  VB                     igX       LvjriiiQ            B                     |\n");
	printf("                                RBi         VBQY                          B                    gQ         ii iii kv          BRvPJ                  |\n");
	printf("                              VBj        iBBu         LRBi               Br                    iUJVkuBI        irUB        iQVD  rQq                |\n");
	printf("                            iBg        iBBi        vQBI                UBi                           irKPSIXXXuvi iB      Jd   Bv  iMg              |\n");
	printf("                           EBi        BBi       iDBPi                vBP                                            gKYYBQB     IB   iBX            |\n");
	printf("                          QD        kBr       VBMi                 PBq  dE                                              Q vM      BI   uB           |\n");
	printf("                        vBi        BB      sBBJ                 uBBr   Bq                                               B  B       Md   iQ          |\n");
	printf("                       ZB         QB   rSQQU                 kBBJ    QB                                                QL  B        Qv   Qr         |\n");
	printf("                      BB          rMEDZUr                ibQQv     kBv rQ                                             PQ   Q         B   Qr         |\n");
	printf("                     PB                              ikQQPi      LBd   bB                                            Qd   SP         qg  B          |\n");
	printf("                     B                           iVRBPv        vBg     B                                           JBr    B           ZEQ           |\n");
	printf("                    RP                      ivPQQqr          sQR      MQ                                         YMJ     Bv                         |\n");
	printf("                    vB                 ijPQREYi            KBP       sB                                         UB     YBr                          |\n");
	printf("                     vQguviiiiIrvkKggRdIvi              iQQj        IB                                           SqUuPds                            |\n");
	printf("                        rvjsvBbrrii                   PBgi         BB   rP                                                                          |\n");
	printf("                             B                     IBBv          iBV     iB                                                            i            |\n");
	printf("                            rB                 iVBBY            BB        Bv                                                 iM        V            |\n");
	printf("                             Bv             vEQgv             VBL         B                                                  Ev        M            |\n");
	printf("                              RBIii   irUdRZui              uBb          BZ                                      K           Q        iZ            |\n");
	printf("                                iUVPKKjri                 UBd           QB                                      Qu          Rv        Mi            |\n");
	printf("                                        Z               EBq            BB                                     iBr          iB         B             |\n");
	printf("                                       Bi            vBBv            rBu    BX                               IB            B         Rv             |\n");
	printf("                                       Bi         rDBqi             BB     vB                              iBu            B          B              |\n");
	printf("                                       vBi    ikdRVi              RBi     vB                              PQ             Bi         Bi              |\n");
	printf("                                        iPDDDPui u             iBBv      SB                             LBv             Bi                          |\n");
	printf("                                                uP           KBQi       QB  i                         iBI             rB                            |\n");
	printf("                                                sQ       iqBQv        iBS   vB                      iQb              PB                             |\n");
	printf("                                                 bQSsIqgEIi          DBi    iB                    iQb                                               |\n");
	printf("                                                   iii             UBk      Bdk                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#04");
	Sleep(1500);
	gotoxy(110, 51);
	printf("내가 앵무새 인형이 된다 해도");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd05() // 고양이 팔을 가진 상태에서 고유 스킬 3번 사용, 마무리 일격
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 도리베어가 냥냥펀치로");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" 마무리 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 가했어요!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("도리베어 : 받아랏!! 냥냥펀치!!!!!!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 푸쾅!!!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("공주 : 꾸아아악!!!!!");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("시스템 : 공주는 강력한 솜뭉치에 맞아");
	Sleep(2000);
	printf(" 그대로 심장에 타격을 입어 쓰러졌어요!!");
	Sleep(2000);
	gotoxy(x, y + 3);
	printf("공주 : 끄...으으윽...");
	Sleep(1000);
	printf(" 이 것이 냥냥펀치의 위..려..ㄱ");
	Sleep(2000);
	gotoxy(x, y + 4);
	printf("도리베어 : 냐옹");
	Sleep(2000);
	system("cls");
	gotoxy(x - 13, y);
	printf("시스템 : 그렇게 공주네 집은 고양이 왕국이 되었답니다.");
	Sleep(3000);
	system("cls");
	printf("                 :Q        ..                                                                                                                   .PsP|\n");
	printf("                  iK                 Yi              r                                                                                 :gi     rQ  U|\n");
	printf("                                   .Ji               Bs   LQY   i.                                                                     L1:X1Jj7Y   :|\n");
	printf("                                                    iv5::Ei jPvUdE                                                                     rK           |\n");
	printf("                                               ...  2: EL    .r  g                                                                     g.      .    |\n");
	printf("         .::.           :::.                7IJrir5 P           .Z                                                                    Q.   :i .I    |\n");
	printf("          .rr7i       Yui7i:2L             11     qBQii:..       R                                                                   5r      rIE    |\n");
	printf("                     vL q v2 SL:7i7L.      Q   .SY:  .::rv11si  iBrvXi                                                               B           .L2|\n");
	printf("                     u. 2:L. rB:.i..qi     rI.uX            .rjqB    Zv                                                              U2.     .ivuY: |\n");
	printf("                    iiBI.       Q.:1 g.      ZS                 7P    B                                                               :LssLsB::     |\n");
	printf("                  7q. ..   i77: X. U.:S      M                   .B   M.                                                                   :j       |\n");
	printf("                 .Q  Yiv  P7  sj ur7 qi     B  .5L                .Q ig                                                                    K:       |\n");
	printf("                 7U Yv B  Q    B  .v1i   .Yg.  sBB7     QBBb       ZPr                                                                     Q        |\n");
	printf("        .         B  vv   vUi7E.  X1   7XUi             :SBD       jr                                                     1         :Q     Q        |\n");
	printf("     .i7rr:       .br. :r.  ..    U: iEi                           d:                                                    Qsg       uI:Q    B   vB.  |\n");
	printf("                    .ir..P1       :S M            7rq    .         B                                                    Q. r5vL7r:P5  vX   Q.  M.buL|\n");
	printf("                          rg:      LB.        7v  UQq    :B       UU                                                   ig      ..ir    Zi  .UrZd    |\n");
	printf("                            KP      5S       MS.i277Xr:..:Q      vE                                                   u5.               SL   DY     |\n");
	printf("                             :gY     qU      .ir:    .i7ri     :qr                                                   Mi    r.  .:       .g  R.   .  |\n");
	printf("                               vDr    rPu.                  iPLdZ5.                                                 57     2:  :Y       iS g.   7r  |\n");
	printf("                                 Ib.    .L1jrr.... ...:ii7vLr    :5q                                                D.       SY         g. Z      .r|\n");
	printf("                                  .Uqi       dBiriBUr:..:.         iQ                                               iZ       v7       .Xv i2      .i|\n");
	printf("                                     7217i:.iK.   Z   :Yvr7LLQQU7   :M                                               sP.          .ir1v    Q        |\n");
	printf("                                        .:ii:    i5 id..       rBE:  Pr                                               .uIL7::iL7uj7XR   B7  SJ7i::..|\n");
	printf("                                                 I: B            PK7  Q                                                   ..rBr     7b :rYi   .::.sB|\n");
	printf("                                                 b. M    .    U. R.I  B                                                     g        7jr. q      .P |\n");
	printf("                                                 D  Q   RB   rB7sv    Q                                                    B          vB :2      B  |\n");
	printf("                                                 P: .ZvSviSvgY        B                                                   r5           g P.     P:  |\n");
	printf("                                                 sL   .     dr       Us                                                   Ki         ..BI5      di  |\n");
	printf("                                                  B          Yb:    iE                                                    rg  .irLjJY7r..   Rg.  j7r|\n");
	printf("                                                  di           JILrUXj                                                     ivvri.          B  R:. ..|\n");
	printf("                                                   B             ..  S:                                                                   J1   :iirr|\n");
	printf("                                                   .Q                B.                                                                  :M.        |\n");
	printf("                                                    .b              57iJu:                                                              ds          |\n");
	printf("                                                 ivviUB7         :5Bs    7Kj                                                           bi     B   K.|\n");
	printf("                                                iM    .JRK:  .7j5v. rK:    :KI.                                                        Q        r   |\n");
	printf("                                                v1       :Bgi7.       UP     .5P.                                                      B       iBi  |\n");
	printf("                                                 B         q:          .ZL     .KX.                                                    :Q           |\n");
	printf("                                                 7d         P7           vD.     .PS                                                    .q1i.     .r|\n");
	printf("                                                  2q         M:           .bI      :gr                                       .r. :7r:     .i77rjBsr:|\n");
	printf("                                                   LD         B             rg:      IP                                   ..vr.Pr7  r1         Z.   |\n");
	printf("                                                    :R:       :D              PI      :Q.                              .7ri.         .I       B     |\n");
	printf("                                                      X2       Q               id:      Z                             iJ.  i          J.     57     |\n");
	printf("                                                       7Q.     d.                KP     D                            :J    Bi . .Q:   .v     Q      |\n");
	printf("                                                    rI7iuQ7:   Q               I7iEQs7  Q                            vr      jQ        s     Q     .|\n");
	printf("                                                   :Q     .:  rP              Q.       br                             77:             75iiri.rbrJvYr|\n");
	printf("                                                   .Q         Q.              SJ      7Z                                .1qri:.....i77.     ..i1I   |\n");
	printf("                                                    iZr     ig:                sPr. .IP                                 .r    ..:::.            iY  |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#05");
	Sleep(1500);
	gotoxy(110, 51);
	printf("내가 고양이 인형이 된다 해도");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd06() // 도리베어 팔을 가진 상태에서 공주 처치
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 도리베어가 자기 팔을 있는 힘껏 휘둘렀어요!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템: 그렇게");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" 마지막 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 가했어요!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("도리베어 : 내 공격을 받아랏!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("공주 : 크흐하!!악!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("시스템 : 공주는 그렇게 마지막 일격에 쓰러졌어요!!");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("도리베어 : 내 팔이 떨어져도 내 실력은 녹슬지 않았군!");
	Sleep(3000);
	gotoxy(x, y + 3);
	printf("           드디어 내 팔도 있으니 이제 평화로운 나날을");
	printf(" 보낼 수 있겠다!!야호!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 공주네 집에서 자신의 팔을 갖고");
	gotoxy(x, y + 1);
	printf("기뻐하며 평화로운 나날을 보냈답니다.");
	Sleep(3000);
	system("cls");
	printf("                                                                                   ii                         VQUBi                                 |\n");
	printf("                                                                                MbVkVKBv                   vgbi   Bv                                |\n");
	printf("                                                         iri         iirvLvvri Bi      Bg                Kbv    URiBu                               |\n");
	printf("                                                       dRkvuB   ivuUuvriiiiiivuBji      Bv               Qj  iEQv   Bs                              |\n");
	printf("                                                     uQr    uBrkvi               XQr    rB                ggISi      Bi                             |\n");
	printf("                                                    vB     ibi                     RM   UB                 SB     rBBBB                             |\n");
	printf("                                                    Q     uR                        VB kB                   iD     ri                               |\n");
	printf("                                 SBuPu              B    iB                          MB                    iPBQ                                     |\n");
	printf("                                  Q  rBR            iBi  B                            Q                    RBQi                                     |\n");
	printf("                                  iB   KB             jvBg                            Bi                                                            |\n");
	printf("                                   rE                   B                             gk                                                            |\n");
	printf("                                    BL                 gq              ijku           Br        isIkUr                                              |\n");
	printf("                                 QBBB                 iB        SqX                   B       rBqiiiiuBq                                            |\n");
	printf("                                 gv                  vB            uLii              Bv     rQD        EB                                           |\n");
	printf("                                                    UB             Qkg              Bk    uQK           Bk                                          |\n");
	printf("                                                    B                             UB   rEPr      iB     iQ                                          |\n");
	printf("                                                   iB                           vRU ikXv          Bi    QV                                          |\n");
	printf("                                                    BV                        vXXsJYi          ibbvPMdgMr                                           |\n");
	printf("                                                     BMi                 iuBBBBZR            LQgi                                                   |\n");
	printf("                                                      rRBui        ivUZgXMBv   iXdY      iUERu                                                      |\n");
	printf("                                                         YEQgQMQMMEPYi   Q        VBvvqgPUi                                                         |\n");
	printf("                                                                      ivB           BQ                                                              |\n");
	printf("                                                                    jb Qr            MQ                                                             |\n");
	printf("                                                                   Qk  B              BU                                                            |\n");
	printf("                                                                 iBr   B               B                                                            |\n");
	printf("                                                                bB    iB               Q                                                            |\n");
	printf("                                                              iBv     Bu               B                                                            |\n");
	printf("                                                             XB     rQB                B                                                            |\n");
	printf("                                                            BD     ZPiB                B                                                            |\n");
	printf("                                                       i  vBi    vBr B                rB                                                            |\n");
	printf("                                                     QduXBQ     BB  Bv                Qi                                                            |\n");
	printf("                                                    BI   uq   iBJ  iB                Br                                                             |\n");
	printf("                                                    B        ZB    Br              rB                                                               |\n");
	printf("                                                    IB     YBu     Bi            rBBY                                                               |\n");
	printf("                                                     iZZPdZu       iBi        rZMZg iSBi                                                            |\n");
	printf("                                                                    vBVQBbgDgEki  d    Bq                                                           |\n");
	printf("                                                                   SQ  Bs         Q     BM                                                          |\n");
	printf("                                                                  BZ   B          ug     BL                                                         |\n");
	printf("                                                                 BL   BV           Bv     B                                                         |\n");
	printf("                                                               rB    iB             B     rQ                                                        |\n");
	printf("                                                          i   vB     B               B     BS                                                       |\n");
	printf("                                                         QukDIB     Br               XR     B                                                       |\n");
	printf("                                                        Eg  iB     BK                 B     RK                                                      |\n");
	printf("                                                        UB   u    Bg                  iB    vB                                                      |\n");
	printf("                                                         BK     iBS                   EBKRY iB                                                      |\n");
	printf("                                                          qQPIdRD                    Bi     Bk                                                      |\n");
	printf("                                                             i                       VgviiiQg                                                       |\n");
	printf("                                                                                       rJjsi                                                        |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#06");
	Sleep(1500);
	gotoxy(110, 51);
	printf("내가 곰인형인 것이 제일 좋아");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd07() // C 뿌리기 패시브와 F맞은 성적표를 가진 상태에서 F맞은 성적표 사용
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 도리베어는 공주에게 F맞은 성적표를 보여줬어요!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("         공주는 자신의 F맞은 성적표를 보고 인생의 현자타임이 온 것 같네요.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("아닛...?! ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("도리베어는 자신도 모르게 c뿌리기를 사용하였어요!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("공주 : ..............");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 공주는 그 상태로 멘탈이 나가버렸어요!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 공주는 그 상태로 진짜 나가버렸어요!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 탈주한 공주의 집에 입주하게 되었답니다.");
	Sleep(3000);
	system("cls");
	printf("                             Mi              i           s                  ur                       iJki                                           |\n");
	printf("                              Di                         i                iL                       vVv                                              |\n");
	printf("                               v                                         ri                     ijui                                                |\n");
	printf("                  i                                                                           rks                                                   |\n");
	printf("                   iri                                i                                     vIr                                                     |\n");
	printf("                     rsi                       iB    vqP   iB                            iuui                                                       |\n");
	printf("                       rjr          iYirvr     g M  rP  R  Svd                         ikL            ii                                            |\n");
	printf("                         ivri      vv    iXi  Ui is D    D d iq                      rIr            iVrirYvi                                        |\n");
	printf("                            ii    iU       kr b   gB     iBv  Pi   vrirvi          LUi             IY      vJv                                      |\n");
	printf("                                  I         sQ            i    Q  S     iJr      vJi             rK           LJi                                   |\n");
	printf("    iiii                          J          u                 vir        ru    i               us              iUv                                 |\n");
	printf("        ivLi                      iD         D                 iBP         ik                  Ki         irki    iYui                              |\n");
	printf("           ivJLi                 sir         ikLii        iivusi P          vv               iP      iiYsvi  g       vui                            |\n");
	printf("               iYJLi           iK               iirrvvvvvrrii                X              iq    rvLri      rD        vVi                          |\n");
	printf("                   rYuri       d                                             ki            rV    iv        ruv           vUi                        |\n");
	printf("                      irYi    V                                              K            Yj      K      YIi               sY                       |\n");
	printf("                              I             ig                            irv            uv        B   Zr                   bi                      |\n");
	printf("                             ui            iRr   iL                      irP            ur         B   g  iirv              q                       |\n");
	printf("                             P         j iYiii   I S    Bv  Li              u           q          vv   Eri   XY            P                       |\n");
	printf("              iii            k       iBPri   U  q   Si iu jvBIj           Piii          X           g       irJk            E                       |\n");
	printf("                iirri        K    rvri       iuSi    iQD    i ibi         iSkU           b          b    rvJi               d                       |\n");
	printf("                    iiii     q    M              s    iiiii     Mi         rig            K         iS   B                  Z                       |\n");
	printf("                             sr  rr           iviiJLvvi    ivsi  ki        X               vvv       Q   ik                 P                       |\n");
	printf("                                rj      iirrrii               Ji  ki       k                Vi       Jv   B                iI                       |\n");
	printf("    iiiiii                    isr   LVri               vbBQBB      q       s                Li        Qivur                Lr                       |\n");
	printf("         iiivvvriii      ivrrii     BBBBBBK  Q  Z  k JBBBBBVu       u  JrivK                u         rL                   D                ii      |\n");
	printf("                       iUi        iv BBRbV   s  M  s  Liv i         MiLi    u               si                         iiiur              Ui ivr    |\n");
	printf("                       K        vvi   i                 J  j       rBk      P        ivrii  vi   iQiiiiiiirvLvvvvvvvvrriii               vQiiiiQ    |\n");
	printf("                       K      iu      q                  u rv          i   iu        S   iiiJv   vv  i i                               iSr     iVi  |\n");
	printf("                       ui    vv      Lv     vrrrrriii    vi S         ri   q         J  i        vr                                 IrPZ         Zi |\n");
	printf("                        P   iv      Jr     P       iiLi   q  P           iI          Y Qr iiirrriSi                                vu vr   i     iu |\n");
	printf("                         X  X      ki      b          E   J  rv    vi  iJr           v K                                           rX  S         Yr |\n");
	printf("                          Yus     ki       K          P    i  I   iU iii             rir                                            Ysiid i      grr|\n");
	printf("                           iSi   ui        Ji       ir     u   v iu                  rv                                                 iS      dv  |\n");
	printf("                             rsirv          svirrviii      vi  vQi         svsJ      Sv                                                  Q     ujvv |\n");
	printf("                                kvi                         vivv         Vr   iVr    Bi                                                  rP   Pv  rJ|\n");
	printf("               i                  ivvii                     iS           ri     vS   B                                                    ruYJ      |\n");
	printf("          iiiii                       irvrrii           irvEu     i   iii EViis   P                                                                 |\n");
	printf("                                            iiirrrriiSsrii  iDViiiiiiiii     is    B                                                                |\n");
	printf("                                                    YB        vi          iirV   iur                                                                |\n");
	printf("                                                  ivvi         iIiiirrrrii   SiiIr                                                                  |\n");
	printf("                                                 vr j           vi            Ki                                                                    |\n");
	printf("                                               vv  JS           iB                                                                                  |\n");
	printf("                                             rL  isiU         iSviuL                                                                                |\n");
	printf("                                          ivv  ivi  rv iirvYrii    iuui                                                                             |\n");
	printf("                                        iki  isi     JQi              vuv                                                                           |\n");
	printf("                                         u  vi        P                  vur                                                                        |\n");
	printf("                                    i     ri          v       i i i        Yq                                                                       |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#07");
	Sleep(1500);
	gotoxy(110, 51);
	printf("그녀의 소중한 것은");
	Sleep(3000);
	system("cls");
	exit(0);
}

int TrueEnd08() // 경청 패시브를 배운 상태에서 공격, 아이템 사용없이 방어만 5회 사용, 경청 패시브를 습득했을 때 방어를 할 때마다 대사가 나옴
{             // 1회 : 공주 : %&^$#%@!!#%!%!%##%^$#%!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, 2회 : 공주 : $#^%$&*%^$^#, 3회 : 공주 : ㅆ>>>ㅡㅡㅢㅣㅣ>>>ㅃ>>>>>ㅢ>>ㅌ>>>> 도리베어: (조금 진정된 것 같다), 4회 : 공주 : 으>>>>>으으ㅡㅡㅇ>>> 도리베어: (흠..조금 더 기다려보자)
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("공주 : ㅜㅜㅠㅓㅗㅜㅏ우ㅜㅠ");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("도리베어 : (왜 화가 났는지 물어보자)");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("공주 : 헊>>> 나를 이쌍하꼐 뽀찌않ㅇ는 얘는 너까 처음이야>>!!ㅠㅠ");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("       모뚜까 날>> 한씸하꼐 쳐따뽰는뗴 >> 쩡말 쓸펐어>>>");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("       냬 쒸쁘뜨키까 빠찌찌않아써 너무 쓸펐어ㅠㅠㅠ 으윾>>");
	Sleep(3000);
	gotoxy(x, y + 3);
	printf("도리베어 : (공주의 쒸쁘뜨 키를 빼주자)");
	Sleep(3000);
	gotoxy(x, y + 4);
	printf("공주 : 내 쒸쁘뜨 키를 빼주어서 고마워 역시 너 밖에 없어ㅠㅠ 화풀이해서 미안해ㅠㅠ");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 공주님은 화가 풀렸고 도리베어와 공주님은 화해를 했어요!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("         도리베어는 공주님과 집에서 다시 평화로운 일상으로 돌아갔답니다!");
	Sleep(3000);
	system("cls");
	printf("                                                                   .7r:     Q:    :Q                                                                 |\n");
	printf("                           Y1j                                    ig .7K7  Q.      jJ                                                                |\n");
	printf("                           Q ur                                   :d    7XE2       iK                                                                |\n");
	printf("                           s. r r7rb                               5Y     q        b:                                                                |\n");
	printf("                            rKYsr.7r                                25             B                               :Lv.                              |\n");
	printf("                       .rrirKBXi:bP.                                 ibr          R:                              Pj .M:                             |\n");
	printf("                      :B7ir:B..B   qr                                  vPr       uI                              Y5    Q                             |\n");
	printf("                       ..  u  q1u   B                                    7IJ.   iM                       IJLs5r  Q     Sr                            |\n");
	printf("                          iI Pi :1L17                                      .vvi7B                       g:    7K:q     r1                            |\n");
	printf("                          iPu:                                                 E                        B       BB     17                            |\n");
	printf("                                                          .i   :I                                       ig      .v     Q                             |\n");
	printf("                                                          QRr v5B.   .                                   rZ.          :Z                             |\n");
	printf("                                              ::.   BLLi.E: 5g7 :u 1J7vY2r                                .PJ         B                              |\n");
	printf("                                            .Ziir1U.:u .ir   :   Q27     vZ                                 iPL.     q7                              |\n");
	printf("                                            Q.    .1.2 .:iLLLr7rrij       rP                                  :I5i  :g                               |\n");
	printf("                                            D.      . .:.                  B                                     7s7d.                               |\n");
	printf("                                            .R.   .                      :q                                                                          |\n");
	printf("                                             .YJ7BL       I              Bi                                                                          |\n");
	printf("                                                 Z      . Bu  ..          1r                                                         r:              |\n");
	printf("                                                :I     DBS rS.7B7:.  :77  .B                                                        g:UJ             |\n");
	printf("                            ::                  :K  :vL           7j27 .M :Br                                                      .P  Q             |\n");
	printf("                           q77P   .ii:           Q  q               .   B  D                               i.                   ..  d  P ...         |\n");
	printf("                          :d  LL.XY::iu5i        .25i  ∧  ∧       B:vS:  E.                        :rrrrB.sY                vE::i:g: BJi:rE        |\n");
	printf("                          2i   Bq       XY        PS     ▽        Su.    .Q                   7vvIiiv...:r7gr                :Ki.  .gsr   vP        |\n");
	printf("                          P.   .         B       iI               j5     :Q                    Z.:E         iP                   .Bg.gEiBir.         |\n");
	printf("                          d.            7P       Q:             ru:  :ivIU                      rB           72                  X  :Lu .U           |\n");
	printf("                          Z.           Jd        .bvi........7Ds7rLrri:.                        q:  /   ＼   iS                 B: 2u  d.PY          |\n");
	printf("                          b.         iEL           .:rrr:.7BbKiiZu.                            Q.    ▽      Z.                 iv7.    iY.          |\n");
	printf("                          q.       iP1                  .Ur       BPr                         .g            XE                                       |\n");
	printf("                          U:     vqJ                   rYZ        S 27                         R:        isPB.sr                                     |\n");
	printf("                          r:  :1Ki                     B .P       K  B                          s1J77:uQBi  .I 7P.                                   |\n");
	printf("                           .YIL.                      di  gS:YivvPQ  .R                              .DQ     17  PY                                  |\n");
	printf("                                                     P7  Bg:: :.  iQ  7K                             ED       Q   iKv                                |\n");
	printf("                                                   rP. .gJ         SQ  vP                          .gB.       Q     .5u.                             |\n");
	printf("                                                 i1:  5J            g5. iD.                       7sR         Bs:   7sSB                             |\n");
	printf("                                                 giLb1.             b P:  Er                     B.s         Q. rYv2bi:                              |\n");
	printf("                                                  qq.               K. KY  vX          ::        MBB       .Zr                                       |\n");
	printf("                                               .II                  7J  i57:Q:        7E:LUr:r7v: :B5:  Y2IL                                         |\n");
	printf("                                              2q.                   iX                :D   :.   :77  :igI Z.                                         |\n");
	printf("                                             Di                     :q                 7q:   .J2i      Q  7s                                         |\n");
	printf("                                            7S                      rU                   rsLJr.       Q:  Yv                                         |\n");
	printf("                                             E7                     2r                              ig.   di                                         |\n");
	printf("                                            rrjQv.                  B                             rur    ig                                          |\n");
	printf("                                 U7vYs:   r1:77:.uIY:              sI                             B7 ..:UP                                           |\n");
	printf("                                 B   .L1rv..Xi     .7Jj7i         jP                               .irri.                                            |\n");
	printf("                                  qj.     sS            :MbUvJvsJIi                                                                                  |\n");
	printf("                                   .s1YivI:     :i:.   :5 D                                                                                          |\n");
	printf("                                       .        B:.rvYS7 iu                                                                                          |\n");
	printf("                                                :b.     .Q                                                                                           |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("True Ending_#08");
	Sleep(1500);
	gotoxy(110, 51);
	printf("그녀의 하나뿐인 곰인형이니까");
	Sleep(3000);
	system("cls");
	exit(0);
}

int NorEnd09() // 패시브 사용없이 공주를 처치
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("시스템 : 공주님은 마침내 도리베어의 ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("마지막 일격");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 맞아버렸어요!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 공주님은 일격을 맞고 쓰러졌어요!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("공주 : 끄으으으윾…. 내가.. 지다니..");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("도리베어 : (공주를 밖으로 몰아내자)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 도리베어는 공주님을 밖으로 내몰았어요.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 그렇게 도리베어는 쓰러진 공주의 집에 입주하게 되었답니다.");
	Sleep(3000);
	system("cls");
	printf("                                                                           k                                                                        |\n");
	printf("                                                                          iXLrii                                                                    |\n");
	printf("                                                                        iQi    rRvUsi                                                               |\n");
	printf("                                                                   iIVukB       UJ                                                                  |\n");
	printf("                                                                        B      rBi        iirii                                                     |\n");
	printf("                                                                        BEi ivbu iIV         iivJuYri                                               |\n");
	printf("                                                                       Qr vvvB                     iLuILi                                           |\n");
	printf("                                                          vv          sj     B                         irISJi                                       |\n");
	printf("                                                       iSJi                  i                             isVji                                    |\n");
	printf("                                                     sXv                                                       ii                                   |\n");
	printf("                                                             iB     ivr                     B                                                       |\n");
	printf("                                                             B     KSiiUP       rv          JV                                                      |\n");
	printf("                                                            gr     B    gX rii EiiB          B                                                      |\n");
	printf("                                                           vZ       PrXSi  iirMQ  Ri         iQ                                                     |\n");
	printf("                                                           B         Bv         duq           Pv                                                    |\n");
	printf("                                                                    Bi           Br            g                                                    |\n");
	printf("                                                                   Qv             Q            iv                                                   |\n");
	printf("                                                                  Pu              B                                                                 |\n");
	printf("                                                                  B              EJ                                                                 |\n");
	printf("                                                                  Kqi           qZ                                                                  |\n");
	printf("                                                                   iUquvivirvuIui                                                                   |\n");
	printf("                                                                        Mgiii  Y                                                                    |\n");
	printf("                                                                       rd      PV                                                                   |\n");
	printf("                                                                       B        B                                                                   |\n");
	printf("                                                                      Qi        iQ                                                                  |\n");
	printf("                                                                      B          Q                                                                  |\n");
	printf("                                                                     rZ          B                                                                  |\n");
	printf("                                                                      B       isQ                                                                   |\n");
	printf("                                                                      iBvjUYsPBrP                                                                   |\n");
	printf("                                      Qi  PB    ii                    Xi Bv  is B                                                                   |\n");
	printf("                               i     VKDikv X bjrLqK                  B  B   Ur B                                                                   |\n");
	printf("                         VKUSr BLSv  Q  BB  BB     rB                B  Rv   Pi Ri  iiiiiii                                                         |\n");
	printf("                        Bv   rkB  iYZi      QE      Mr            iJBr iBrrJ E  igiuriiiiiivkSi                                                     |\n");
	printf("                       vD      Bv         idv       Ri       iYISvsB  iB     gi  QYirrvrri    KI                                                    |\n");
	printf("                       Qi    rdiiuuuYsYukVv       iid    ivXIvi   igiuZ      Pv   Q      iiLJLvg                                                    |\n");
	printf("                       iBi  iQ             i      iB  iuKsi         i         B   Q                                                                 |\n");
	printf("                         YviZ              BkP      QvL                       iEjJP  ivujuJuJjLr                                                    |\n");
	printf("                           BB  iI   BQ  i P  iBVUi  Ki                           LBrii         rgr                                                  |\n");
	printf("                          rr BBvK  Zv ZigBb    BgPi Rd                            Q  iivYJYsvi   Qi                                                 |\n");
	printf("                             QivrUSi    Bq        Bu  B                           Bvii      iYZv vD                                                 |\n");
	printf("                            Xv        iSi          iiiR                           B            vSq                                                  |\n");
	printf("                           iB  iii  vQu              D                          JQi                                                                 |\n");
	printf("                           B     iDBdursjJLv    LurDQv                      iJqqr                                                                   |\n");
	printf("                           B     jv           igS    ivuXkkuuJsYsLssuuVIVkIYvi                                                                      |\n");
	printf("                           vgr              vbS                i                                                                                    |\n");
	printf("                             LqVvii iiivuIVvi                                                                                                       |\n");
	printf("                                iirvvvii                                                                                                            |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("Normal Ending_#09");
	Sleep(1500);
	gotoxy(110, 51);
	printf("네가 결국 해냈어");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd10() // 인피니티 건틀렛으로 공주 처치
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("공주 : 난 너보다 한 수 위이다. 필연적인 존재다!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("시스템 : 그 때, 도리베어는 ");
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("인");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("피");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("니");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("티");
	Sleep(150);
	printf("   ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("건");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("틀");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("렛");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 사용했어요!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("I ");
	Sleep(1000);
	printf("am ");
	Sleep(1000);
	printf("DoriBear. ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("딱-☆");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 도리베어가 핑거스냅을 썼어요!!!!");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         그러자....");
	Sleep(1000);
	gotoxy(x, y + 2);
	printf("         공주님이 서서히 가루로 변하기 시작했어요!!!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("(스스스....)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("공주 : 이게 뭐야...?!");
	Sleep(500);
	printf(" 내 몸이...");
	Sleep(500);
	printf(" 가루로...");
	Sleep(500);
	printf(" 변..");
	Sleep(250);
	printf(" ㅎ..");
	Sleep(250);
	printf("ㅏ..");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("(스르륵)");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("도리베어 : 이로써.. 이 집은 내 것이다..");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 비록 생물체 중 절반이 사라지긴 했지만 그래도 집에 돌아와 기쁜 도리베어는");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         공주님이 살았던 집에서 행복하게 잘 살았답니다!");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                      DVPS                           |\n");
	printf("                                                                                                               iBbv  bV  gU                          |\n");
	printf("                                                                                                               Q  Lqdg    Qi                         |\n");
	printf("                                                                                                              Qi    i      Bi     LJvuv              |\n");
	printf("                                                                                                         iBvvLB   iiivduii iiivLjQ    vX             |\n");
	printf("                                                                                                          vQ    rUri            irjr   Pi            |\n");
	printf("                                                                                                           ig  Ir                  rdi iX            |\n");
	printf("                                                                                                             Bvi                     Qivr            |\n");
	printf("                                                                                                           iY                        sBQ             |\n");
	printf("                                                                                                       jvrsg         Qv     v         SU             |\n");
	printf("                                                                                                     rd   B        PrPPr    QPvii     BQ             |\n");
	printf("                                             EUuuKds                                                 B   iV        BQ  iiisIEi iuEiiriiB             |\n");
	printf("                                          i Bv     uB                                               id   iP    iiiE   ivrur ii   DQi  Qi             |\n");
	printf("                              iLr   iXZgPKVIKKbEv   rB                                               B   J     VQi  Bi ii  gEkjv      M              |\n");
	printf("                            rBL iBBDVi          kBV  B                                                QbiZ     Q  iuS     Zv   vk     B              |\n");
	printf("                           rB   qi                jBB                                                   rB    br ir       iu   Ii BvJg               |\n");
	printf("                  vi       B   B                    vQV                                         iv        gvsJi dsvB        DRgr Br                  |\n");
	printf("                   Bi      B   B                      UBi                                            iK    iB  kv  Bi   iii     bU                   |\n");
	printf("                i   BS     iBUiB     __         __      BU                                      iQi  jB      g Bu JB  YriirIQ  Id                    |\n");
	printf("                ru   v       iiSP          BBB           Bi                               vU    BBQ      BL uY  gZP  Pi iri  idY                     |\n");
	printf("                  us            B          kuV           BI                                     iv       r  B        Iui   iKu                       |\n");
	printf("                   rv           B                        B                                   i      X   jb  rQi          ukBririvPvi                 |\n");
	printf("               i         BqZ   iB                      iBi                                   J     QBi        LJuLkUvviiqBQ      Z Di                |\n");
	printf("             vvLi       Bi VQ  Yg                    iED                                        Bi      i             rBRBB      b  B                |\n");
	printf("                        B   IR  B                 LUdBv                                   gi    Bi         Vr v  Bi  JBBUV Q     Ui Pv               |\n");
	printf("                 ii    iB    JQ  BSi         irKDDKBBrivqU                                vi         Ju    v  QbgBiM BU rB Z     Jr  B               |\n");
	printf("              iLqki     B     iBi  vXqKuIqXVBZvi    VP   iMEi                                    ir  BQ  ujZiMvv vq  BP   Q      Yv  Ri              |\n");
	printf("             iJi        UB      RS     ivMY Q         BS   iRg                             PB   iBB     LBBB B Mv iBr  Vu uB     vv  vE              |\n");
	printf("                  i      BK      iVuuYv  B iP          EB    iBI                           ii             ii   uB  B  iBB  u     id   B              |\n");
	printf("                 gS       BP           iBs Bi           YB     PB                                BB   DX LQB   i Rru  Bi  Bi      M   Bi             |\n");
	printf("                UP         MB       iUMK   B             vB     iBq                              BZ  vBr iB  RJ  M  B  j          LU  iB             |\n");
	printf("                            iBPvrkbgki    iB              DRi     uBi                                          i  K iB UBg  Pi     Qi  Bi            |\n");
	printf("                              ivvi        vD              iQjQi     Bi                        Ui   QY  vB         r  i   ri         B  iB            |\n");
	printf("                                          kP              iB  gRi  iBJ                           i BM  ii   sB   i iP  V V Bi       iE  Qv           |\n");
	printf("                                          KS              kE    sjJv                             i       vBi i    iP   B   L         kd  Bi          |\n");
	printf("                                          vQ              B                                              iK     BB   Q  iQR           BI  B          |\n");
	printf("                                           B            YB                                   ui BB   ii        IBQ iJi   ii            BXvP          |\n");
	printf("                                           YB        iBPLB                                   v  i   VBB    gB  i   BBi   B             iP            |\n");
	printf("                                             QRuBZSSIrBi  B                                          i     BQi s    iD                  B            |\n");
	printf("                                             P  Ej     B  iB                                                 i uiKPr  ZB             BIYU            |\n");
	printf("                                             B  rB     Br  gI                                 q  ii   iB         BB   rPPviSPPr KBBrsBv              |\n");
	printf("                                             B   B      B   Q rXVi                                     M     bg  ki S  Mqvui iLJv dY  Y              |\n");
	printf("                                             B   Q      DK  RBL  Bi                                         jBk jv  K             ik  g              |\n");
	printf("                                             B   Bi      B       B                               PB   JX                dr         Q   g             |\n");
	printf("                                             B   Bv      iB     gP                                    bD   D    Bii  B  uQ          Q  Ei            |\n");
	printf("                                         VkIUB   Bi       UB   gQ                                  i       BE      iiq   iJ         gi  R            |\n");
	printf("                                        B   i    B         dQJQJ                                   ui              Ji  iv           id  gi           |\n");
	printf("                                        Q       iB          ii                                         gL  vr    BBU    g  i         Q  iD           |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#10");
	Sleep(1500);
	gotoxy(110, 51);
	printf("그럼 안녕");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd11() // 인피니티 건틀렛으로 도리베어 사망
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("공주 : 난 너보다 한 수 위이다. 필연적인 존재다!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("시스템 : 그 때, 도리베어는 ");
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("인");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("피");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("니");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("티");
	Sleep(150);
	printf("   ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("건");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("틀");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("렛");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("을 사용했어요!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("I ");
	Sleep(1000);
	printf("am ");
	Sleep(1000);
	printf("DoriBear. ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("딱-☆");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 도리베어가 핑거스냅을 썼어요!!!!");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         그러자....");
	Sleep(1000);
	gotoxy(x, y + 2);
	printf("         도리베어가 서서히 가루로 변하기 시작했어요!!!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("(스스스....)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("도리베어 : 어어..");
	Sleep(500);
	printf(" 왜 내가..");
	Sleep(500);
	printf(" 가루로...");
	Sleep(500);
	printf(" 변..");
	Sleep(250);
	printf(" ㅎ..");
	Sleep(250);
	printf("ㅏ..");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("(스르륵)");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("공주 : 엥 갑자기 왜 쟤가 가루로 변한담");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("시스템 : 공주는 그저 영문도 모른 채 가루로 변해 사라지는 걸 볼 뿐이였어요.");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         그리고 생물체 중 절반이 사라진 것을 곧 알게 되는데...");
	Sleep(3000);
	system("cls");
	printf("                                                                                     iBii                 vUv                                        |\n");
	printf("                                                                                     ZY                                                              |\n");
	printf("                                                                                   igj                                                               |\n");
	printf("                                                                                 kBq                                     PPuSZdi                     |\n");
	printf("                                                                                   B            rbPPdU   ivUVPPdPEPqur  qv    iBg                    |\n");
	printf("                                                                                  Ks           Bq    MBvuvi         ivbEB       uB                   |\n");
	printf("                                                                               PBQ            Br    YJ                  iBZ      Dg                  |\n");
	printf("                                  rZBdi                                          Rv           B    qU                     XQ      B                  |\n");
	printf("                                jBBBQBBR                                       igP            ZS  IE  iv    jkii           UB    BV                  |\n");
	printf("                               kBBubBBBB                                       dPvq            iMBD  ig       ii            BvikBv                   |\n");
	printf("                               BQ   MBBBk                                         vB         iLjY    Y                      gBvr                     |\n");
	printf("                                    BQBBE                                         Bi       sgki             iivvui          Bi                       |\n");
	printf("                                  dBBBBB                                         Q        Bj                rii             B                        |\n");
	printf("                                  uQBji                                                 iQi      JUjv  irui                Bq                        |\n");
	printf("                                   BB                                                   Q             iBiBi               UB                         |\n");
	printf("                                                                                dD                      bi               YB                          |\n");
	printf("                          vEusjPqi   ii                                     vBi    i   vMv                              VB                           |\n");
	printf("                   iBv   uE      PB  BBX                                    jv   vBBL  rBQ                             QB                            |\n");
	printf("                    QsBJ M        iB  i                                       q  dQBQ                                 BE                             |\n");
	printf("                    B  vqBBiivLvr  rR                                     Bv BB        BB  BBu                      ZP                               |\n");
	printf("              BkKPusB     BKii irkSBL                                     P  BBr  BBs  BQ  BBBQ                rXQPBBv                               |\n");
	printf("              B          Er         kZ                                            JBBB      i irvUkJYviiYvVIPqkrKBd   JDdr                           |\n");
	printf("              Bi       XD            BQ                                        iQEv     PBE  iBQi     uBbBQ       uBi    kMZv                        |\n");
	printf("           ii Bv     vBi i            B                              iB    Q   vBQv     LQBi iBBB    Kq  B          Bg      jgMji                    |\n");
	printf("         BJirvv    iMX   Bi         i qu                                   BQi      BBv            vBi  SX           BM        vPQds                 |\n");
	printf("          U       dZ      B         iuqI                                 rB         iYJ    BBB    RB    B             BL           LZgZL             |\n");
	printf("         iiBg  ikMi       iB  rQsYLJvPBP                                 iX     ri          uD  IBi    Bv              B               YbB           |\n");
	printf("       vQii vBQri          BDSdQv       VbbJi                                   Ev   QBi  Jb          vQ               vBKi              MB          |\n");
	printf("       B     Q          v  B       vvLg    rKQq                      k     r         PBB  vBJ  jr     B                 BiYdEDKuii     iXB           |\n");
	printf("      Qu    Bi         iBKQ      Z     i      vBi                   iBi    Bi     r           iBBI   Br                 Bi    iiuqDEDdZSr            |\n");
	printf("      Qs    B          iBv        iii''        iB                          i Bi  iBv    BBv      i   B                  Q                            |\n");
	printf("      vB   vb        i Q   igS         i        B                                    u  BBB  VBQi   iB                 rB                            |\n");
	printf("       dB  Lu        BQ    B BV      sbr        Q                        rBi         r       BBBQU   B                rB                             |\n");
	printf("        vDbBB        iB   uB BX     ZS         iB                         Z   vBi   rV       YBBBB Lridr            vBg                              |\n");
	printf("            XR        B   vBvB     gk          Bi                             iv     BJ  PqU   i   BQBQuuDqvirivVEBBiBv                              |\n");
	printf("             iEd     iB    UZ     EX          ZB                                  P     iBBBB  BBP  iqBB   QbvJvi  Q  Bi                             |\n");
	printf("               B    vB           KZ          QB                              RK      rBi uUUu  KYi L       qi      EY  B                             |\n");
	printf("               Bi gsQv                     vBI                               uk       Ui      iBB BBBQ     B       iB  JB                            |\n");
	printf("                DB                       iBX                                                 BirB iBBB     B        Q   BL                           |\n");
	printf("                 B                     vBB                                        BBB    BB  BB    BZ     Rr        Bi   B                           |\n");
	printf("                 vBi rrv Dqi       ivbBr PviBqi                               iBY vj     BQD     k        Q         Rv   ZP                          |\n");
	printf("                  iEdusJPDvKgZZEgDZSr B ib  iXid                              iQi   Q         EBri  dB   Bv         Bi    B                          |\n");
	printf("                                     qJ      Q  gv                                      ki   BQBBB      QV         iB     B                          |\n");
	printf("                                    iYE       S  VP                                  Ui BBBu BBQBi    rBv          B      B                          |\n");
	printf("                                    v  Q      B   iQi                               iBI  irr uBq  JkVdS           Qi     RK                          |\n");
	printf("                                    iY Qi     BZi   gj                         iBr      vi                       UB     XB                           |\n");
	printf("                                     b  RQL     Qu   VE                         Qs      LBBBi  vBi                PPVXXgu                            |\n");
	printf("                                     D  E        qZ   vQ                                 vL    PBBB                                                  |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#11");
	Sleep(1500);
	gotoxy(110, 51);
	printf("The End");
	Sleep(3000);
	system("cls");
	exit(0);
}

int main()
{
	system("mode con cols=150 lines=55 | title 도리 베어");
	notcon();
	while (1)
	{
		startintro();
		mainintro();
		int maincode = mainchoice();
		if (maincode == 24)
		{
			break;
		}
		else if (maincode == 31)
		{
			system("cls");
			printf("떠 나 지 마");
			Sleep(1000);
			return 0;
		}
	}
	system("cls");
	sna();
	while (1) {
		room = roommove(room);
		if (room == 1) {
			roomin = cRoom1();
		}
		else if (room == 2) {
			roomin = gRoom1();
		}
		else if (room == 3) {
			roomin = nRoom1();
		}
	}


	return 0;
}
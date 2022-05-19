#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h> //true false를 사용하기 위한 헤더
#define MAX_X 40
#define MAX_Y 30
#define MAXBULLET 10


//소스파일 > C++  > 파일명.c로 C파일 만들기
//프로젝트 > 속성 > C/C++에서 sdl 검사 '아니오'로 만들어야지 scanf 사용 가능.
//참고 링크
/* 1. 콘솔창 조절 : http://egloos.zum.com/EireneHue/v/350607
* 2. 플레이어 이동 : https://byunghyun23.tistory.com/4
* 3. 커서 숨기기 : https://geundung.dev/17
* 4. C언어 콘솔창 제목 바꾸기 : https://berabue.tistory.com/59

* 
*/

//마우스 커서 좌표 지정 함수 gotoxy
void gotoxy(int x, int y)
{
	COORD m;
	m.X = x;
	m.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
}

void init() { //콘솔창 크기 지정, 제목 변경, 커서 숨기는 함수
	system("title C언어 슈팅게임");
	system("mode con cols=40 lines=30"); //MAX_X, MAX_Y를 수정할 때 같이 수정해야함.
	HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consolHandle, &ConsoleCursor);
}

struct {
	int exist;
	int bx, by;
}Bullet[MAXBULLET];

void main() {
	init();
	int x = (MAX_X / 2) ;
	int y = MAX_Y - 3;

	//int here;

	int bx=0, by=0; //총알용 x,y 좌표
	bool bullet = false; //총알이 나타나느 여부에 대해 판다.
	//스페이스바를 누르면 총알 발사, 총알을 플레이어의 y-1 좌표에서 등장

	//특수문자와 영어는 한글자가 한 칸, 한글은 한 글자가 2칸취급 받는 듯 하다
	//이동을 반복하기 위해서는 while문이 필요 

	//while (1) {
	//	gotoxy(0, MAX_Y + 1); //x,y좌표 출력 위치 지정
	//	printf("X 좌표 : %d\n", x);
	//	printf("Y 좌표 : %d\n", y);
	//	//플레이어 위치 출력
	//	gotoxy(x, y);
	//	printf("▲");

	//	here = getch();

	//	switch (here) {
	//	case 224:
	//		here = getch();
	//		switch (here) {
	//		case 75:
	//			if (x != 0)
	//				x--;
	//			break;
	//		case 77:
	//			if (x != MAX_X-2)
	//				x++;
	//			break;
	//		default:
	//			break;
	//		}
	//	

	//	default:
	//		break;
	//	}
	//	system("cls"); //화면에 있는 것을 전부 지움
	//}

	while (1) //영상에서는 미리 정의해 둔 헤더파일에서 함수를 끌어와서쓴다.
		//영상에서 함수 역할을 설명해주면 그걸 내가 직접 만들어봐야될 듯
		//아래의 함수는 영상 + 내가 직접 찾은 코드들을 합쳐서 만든 것이다.
	{
		gotoxy(0, MAX_Y + 1); //x,y좌표 출력 위치 지정
		printf("X 좌표 : %d\n", x);
		printf("Y 좌표 : %d\n", y);
		//플레이어 위치 출력
		//gotoxy(x, y);
		//printf("■");


		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			x--;
			if (x < 0) x = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			x++;
			if (x > MAX_X - 2) x = MAX_X - 2;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!bullet) { //발사 중인 총알이 없을 때
				bx = x;
				by = y - 1;
				bullet = true;
			}
		}
		if (bullet) {
			gotoxy(bx, by);
			printf("↑");
			by--; //y좌표가 계속 감소하므로 총알이 발사되어 이동하는 것처럼 보임
			if (by < 0) bullet = false; //총알이 천장에 도착했다면 총알을 숨김
		}

		//플레이어 위치 출력
		gotoxy(x, y);
		printf("■");
		Sleep(50);
		system("cls"); //화면을 전부 지우는 코드
	}
	
	
	return 0;

}

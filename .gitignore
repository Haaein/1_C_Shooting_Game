#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//소스파일 > C++  > 파일명.c로 C파일 만들기
//프로젝트 > 속성 > C/C++에서 sdl 검사 '아니오'로 만들어야지 scanf 사용 가능.
//참고 링크
/* 1. 콘솔창 조절 : http://egloos.zum.com/EireneHue/v/350607
*/

//마우스 커서 좌표 지정 함수 gotoxy
void gotoxy(int x, int y)
{
	COORD m;
	m.X = x;
	m.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
}

void main() {
	int x = 14, y = 28;
	system("mode con cols=33 lines=40");
	//이동을 반복하기 위해서는 while문이 필요 
	
	while (1) //이동 및 잔상 지우기는 다른 코드 참고가 "매우" 필요해보임
		//영상대로하면 잔상도 안지워지고 이동할 수 있는 한계도 이상함
	{
		gotoxy(x, y);
		printf(" ");
		//키보드 값을 입력받는 코드
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			x--;
			if (x < 0) x = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			x++;
			if (x > 28) x = 28;
		}

		gotoxy(x, y);
		printf("▲");
		//Sleep에 1000을 넣으면 1초를 쉰다.
		/*잔상을 막기 위해 Sleep를 넣은 것인데 내쪽에서는 잔상이 계속 남는다.
		다른 방법이 필요할 듯*/
		Sleep(50);
	}
	return 0;

}

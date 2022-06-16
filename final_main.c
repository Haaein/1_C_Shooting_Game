#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <stdbool.h> //true false를 사용하기 위한 헤더
#include <time.h>
#define MAX_X 40
#define MAX_Y 30
#define MAXBULLET 10
#define MAX 30


//소스파일 > C++  > 파일명.c로 C파일 만들기
//프로젝트 > 속성 > C/C++에서 sdl 검사 '아니오'로 만들어야지 scanf 사용 가능.
//참고 링크
/* 1. 콘솔창 조절 : http://egloos.zum.com/EireneHue/v/350607
* 2. 플레이어 이동 : https://byunghyun23.tistory.com/4
* 3. 커서 숨기기 : https://geundung.dev/17
* 4. C언어 콘솔창 제목 바꾸기 : https://berabue.tistory.com/59
* 5. 콘솔창 및 폰트 색 변경 : https://coding-factory.tistory.com/663
*/


void gotoxy(int x, int y) //마우스 커서 좌표 지정 함수 gotoxy
{
	COORD m;
	m.X = x;
	m.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m);
}

void init_game() { //콘솔창 크기 지정, 제목 변경, 커서 숨기는 함수
	system("title C언어 피하기 게임");
	system("mode con cols=40 lines=30"); //MAX_X, MAX_Y를 수정할 때 같이 수정해야함.
	HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consolHandle, &ConsoleCursor);
}

void StartMenu(void) //게임 시작 메뉴 함수
{
	while (1)
	{
		system("cls");
		gotoxy(MAX_X-25, MAX_Y/2);
		printf("별 피하기");
		gotoxy(MAX_X/5,MAX_Y-5);
		printf("아무키나 누르면 시작합니다.");

		if (kbhit()) break;
	}
}

struct ST_OBJECT
{
	int x;
	int y;
	bool bActive;
};//적, 플레이어 모두 사용할 수 있는 구조체

struct ST_OBJECT stEnemy[MAX]; //에너미 전용 구조체 배열
struct ST_OBJECT stPlayer; //플레이어전용 구조체 변수


//별을 만드는 함수 = Spawn();
void Spawn(void) {
	for (int i = 0; i < MAX; i++) //반복을 한 번 할 때마다 하나의 별이 생성
	{
		if (!stEnemy[i].bActive) {
			stEnemy[i].x = (rand() % 30) * 2;
			stEnemy[i].y = 1;
			stEnemy[i].bActive = true;
			break; //모든 배열의 값이 true가 되지 않도록 if문을 종료하고 다시 반복 시작
		}
	}
}

int EnemyProcess(void) //count 반환을 위해 int 함수로 선언
{
	int count = 0;//남아있는 별의 개수를 저장하기 위한 지역변수
	for (int i = 0; i < MAX; i++) { //for문을 통해서 각 배열의 원소별로 발사 모습 출력
		if (stEnemy[i].bActive) { //에너미가 활성화 되었다면(bActive = true)
			count++; //생성되는 별의 개수만큼 증가
			gotoxy(stEnemy[i].x, stEnemy[i].y); //설정된 적좌표(랜덤 좌표)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //출력되는 별의 색을 노란색으로 변경
			printf("☆"); //총알을 출력하고
			stEnemy[i].y++; //y좌표 증가(아래로 내려오는 효과)

			if (stEnemy[i].x == stPlayer.x && stEnemy[i].y == stPlayer.y) //적과 플레이어의 x,y좌표가 같을 때(=충돌했을 때)
			{
				stPlayer.bActive = false; //플레이어가 사라진다.
			}

			if (stEnemy[i].y >= stPlayer.y) //적의 위치가 플레이어의 y좌표일때
			{
				stEnemy[i].bActive = false;
			} //bActive=false가 되어 화면상에서 보이지 않게 함.
		  //수정 필요: 플레이어 총알하고 적총알하고 같이 이동하는 경우가 있음
		}//프로그램이 구동될 때 true가 몇 개 일지 모르니 체크하는 것이 필요하다.(if문)
	}
	return count; //플레이어가 충돌시 생성되는 별(적)의 개수 = 0, count=0이 된다. -> 함수가 종료된다.
}


void InputProcess(void)  //플레이어 이동 조종 함수
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽키&계속 누르고 있다면
	{
		stPlayer.x=stPlayer.x-2; //왼쪽으로 2칸씩 이동
		if (stPlayer.x < 0) stPlayer.x = 0; //화면 끝에 도달했을 때 플레이어의 x좌표를 고정시킨다.
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		stPlayer.x=stPlayer.x+2;//오른쪽으로 2칸씩 이동
		if (stPlayer.x > MAX_X - 2) stPlayer.x = MAX_X - 2;//화면 끝에 도달했을 때 플레이어의 x좌표를 고정시킨다.
	}
}

void Update_player(void)
{
	if (stPlayer.bActive) //플레이어가 활성화라면(= 충돌하지 않았다면)
	{
		gotoxy(stPlayer.x, stPlayer.y); //현재 플레어이어 좌표에
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("■"); //플레이어의 모습을 출력
	}
	else //활성화상태가 아니라면
	{
		gotoxy(stPlayer.x, stPlayer.y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("&"); //&을 출력
	}
	Sleep(50);
	system("cls"); //화면을 전부 지우는 코드
}

int p_score = 0;//점수 저장용 전역변수
void Score(void) //점수 측정, 출력 함수
{
	if (stPlayer.bActive) //플레이어와 활성화일때만
	{
		p_score++;//점수를 증가시킨다
	}
	gotoxy(0, MAX_Y);
	printf("Score : %d", p_score);
}

void main() {
	init_game(); //화면을 초기화
	stPlayer.x = (MAX_X / 2) ; //플레이어의 x좌표가 중앙에 오게끔 초기화
	stPlayer.y = MAX_Y - 3; //플레이어의 y좌표 초기화
	stPlayer.bActive = true;
	int state = 0; //EnemyProcess에서 반환되는 값을 저장하는 지역변수

	int bx=0, by=0; //총알용 x,y 좌표
	bool bullet = false; //총알이 나타나는 여부에 대해 판다.
	//스페이스바를 누르면 총알 발사, 총알을 플레이어의 y-1 좌표에서 등장
	srand(time(NULL));

	StartMenu(); //게임 시작 메뉴 출력 함수
	system("cls"); //게임 시작 전 화면을 깨끗하게 함

	while (1)
	{
		if (stPlayer.bActive)
		{
			Spawn(); //적(☆) 생성 함수
			InputProcess(); //플레이어 이동 조종 함수
		}
		state = EnemyProcess();//적 이동 처리 함수, 충돌시 0을 반환한다.
		Update_player();//플레이어의 활성화 여부에 따른 모습 표시 함수
		Score(); //점수 측정 함수

		if (state == 0) break; //state ==0일때 프로그램 종료
	}
	
	
	return 0;

}

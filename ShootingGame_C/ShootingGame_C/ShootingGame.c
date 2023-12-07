#include <Windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#pragma warning (disable : 4996) // 4996번 오류에 대한 경고 메세지 미사용

#define ESC 27
#define MAXENEMY 10
#define MAXBALL 20


int fx;
int bx, by;
int score;

//이동을 위한 정의 함수
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
//적구조체
struct tag_Enemy
{
	BOOL exist; // 보여줄지 말지...
	int Type;
	int x, y;
	int Delta;
	int nFrame;
	int nStay;
} Enemy[MAXENEMY];

struct tag_Ball
{
	BOOL exist; //보여줄지 말지...
	int x, y;
	int nFrame;
	int nStay;
} Bomb[MAXBALL];

const char* arEnemy[] = {
	" <::^::> ",
	" <=:0:=> ",
	" <=[]=> ",
	" <o00o> ",
	" <++#++> "
};

// 키가 눌렸는지 확인하기 위한 함수
BOOL IsKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0X8000 != 0);
}

int main()
{
	int ch;
	int i, j;
	BOOL bFound;
	int count;

	srand((unsigned)time(NULL)); // 랜덤함수
	system("cls"); //ClearScreen - 콘솔창의 전부를 지우는 기능(Windows.h)
	CursorView(0);

	for (count = 0; ; count++)
	{
		if (count % 2 == 0)
		{
			if (IsKeyDown(VK_LEFT))
			{
				if (fx > 6)
					fx--;
			}
			if (IsKeyDown(VK_RIGHT))
			{
				if (fx > 6)
					fx++;
			}
		}

			// 그 상황에서
		if (kbhit()) // 만약 키입력이 되었다면...
		{
			ch = getch(); // 입력한 키값을 받아와서 ch에 대입
			if (ch == 0xE0 || ch == 0)
			{
				getch();
			}
			else
			{
				switch (ch)
				{
				case ' ': //SpaceBar가 눌린 경우...
					if (bx == -1)
					{
						bx = fx;
						by = 23;
					}
					break;
				case ESC: //ESC가 눌린경우...
					goto end;
				}
			}
		}
		// 적군 생성
		if (rand() % 50 == 0)
		{
			for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++)
			{

			}
			if (i != MAXENEMY)
			{
				if ((rand() % 2) + 1 == 1)
				{
					Enemy[i].x = 5;
					Enemy[i].Delta = -1;
				}
				else
				{
					Enemy[i].x = 75;
					Enemy[i].Delta = -1;
				}

				for (;;) // 무한반복
				{
					Enemy[i].y = rand() % 10 + 1;
					for (bFound = FALSE, j = 0; j < MAXENEMY; j++)
					{
						if (Enemy[j].exist == TRUE && Enemy[j].y == Enemy[i].y)
						{
							bFound = TRUE;
							break;
						}
					}
					if (bFound == FALSE)
						break;
				}

				Enemy[i].nFrame = Enemy[i].nStay = rand() % 6 + 1;
				Enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0])); // 랜덤 적기 타입  사실상 5기
				Enemy[i].exist = TRUE; // 적기 보여주기
			}
		}
		// 플레이어 총알 이동 및 출력
		if (bx != -1)
		{
			gotoxy(bx, by);
			putch(' ');
			if (by == 0)
			{
				bx = -1;
			}
			else
			{
				by--;
				gotoxy(bx, by);
				putch('i'); // 미사일
			}
		}

		// 적군과 아군 총알의 충돌 판정
		for (i = 0; i < MAXENEMY; i++)
		{
			if (Enemy[i].exist == FALSE)
				continue;

			if (Enemy[i].y == by && abs(Enemy[i].x - bx) <= 2)
			{
				gotoxy(bx, by);
				putch(' ');
				bx = -1;
				Enemy[i].exist = FALSE;
				gotoxy(Enemy[1].x - 3, Enemy[i].y);
				puts("                  ");
				score += 7 - Enemy[i].nFrame;
				break;
			}
		}

		// 적군 총알 이동 및 출력
		for (i = 0; i < MAXBALL; i++)
		{
			if (Bomb[i].exist == FALSE)
				continue;

			if (--Bomb[i].nStay == 0)
			{
				Bomb[i].nStay = Bomb[i].nFrame;
				gotoxy(Bomb[i].x, Bomb[i].y);
				putch(' ');

				if (Bomb[i].y >= 23)
				{
					Bomb[i].exist = FALSE;
				}
				else
				{
					Bomb[i].y += 2;
					gotoxy(Bomb[i].x, Bomb[i].y);
					putch('*');
				}
			}
		}

		// 적군 총알과 플레이어의 충돌 판정
		for (i = 0; i < MAXBALL; i++)
		{
			if (Bomb[i].exist == FALSE)
				continue;

			if (Bomb[i].y == 23 && abs(Bomb[i].x - fx) <= 2)
			{
				gotoxy(fx - 3, 21); puts("    .    ");
				gotoxy(fx - 3, 22); puts(" .  .  . ");
				gotoxy(fx - 3, 23); puts("..:   :..");
				gotoxy(fx - 3, 24); puts("````::''''''");
				Sleep(1500);

				goto end;
			}
		}

		// 적기 이동 및 출력
		for (i = 0; i < MAXENEMY; i++)
		{
			if (Enemy[i].exist == FALSE)
				continue;

			if (--Enemy[i].nStay == 0)
			{
				Enemy[i].nStay = Enemy[i].nFrame;
				if (Enemy[i].x >= 76 || Enemy[i].x <= 4)
				{
					Enemy[i].exist = FALSE;
					gotoxy(Enemy[i].x - 3, Enemy[i].y);
					puts("             ");
				}
				else
				{
					Enemy[i].x += Enemy[i].Delta;
					gotoxy(Enemy[i].x - 3, Enemy[i].y);
					puts(arEnemy[Enemy[i].Type]);

					if (rand() % 20 == 0)
					{
						for (j = 0; j < MAXBALL && Bomb[j].exist == TRUE; j++)
						{

						}
						if (j != MAXBALL)
						{
							Bomb[j].x = Enemy[i].x + 2;
							Bomb[j].y = Enemy[i].y + 1;
							Bomb[j].nFrame = Bomb[j].nStay = Enemy[i].nFrame * 6;
							Bomb[j].exist = TRUE;
						}
					}
				}
			}
		}

		gotoxy(fx - 3, 24);
		puts(" <<A>> ");
		gotoxy(58, 24);
		printf("점수 : %d", score);

		Sleep(20);
	}
end:
	system("cls");
	gotoxy(58, 10);
	printf("GAMEOVER");
	gotoxy(58, 15);
	printf("점수 = %d", score);
	CursorView(0);
	getchar();
}
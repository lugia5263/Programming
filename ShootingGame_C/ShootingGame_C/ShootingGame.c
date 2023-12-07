#include <Windows.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#pragma warning (disable : 4996) // 4996�� ������ ���� ��� �޼��� �̻��

#define ESC 27
#define MAXENEMY 10
#define MAXBALL 20


int fx;
int bx, by;
int score;

//�̵��� ���� ���� �Լ�
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
//������ü
struct tag_Enemy
{
	BOOL exist; // �������� ����...
	int Type;
	int x, y;
	int Delta;
	int nFrame;
	int nStay;
} Enemy[MAXENEMY];

struct tag_Ball
{
	BOOL exist; //�������� ����...
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

// Ű�� ���ȴ��� Ȯ���ϱ� ���� �Լ�
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

	srand((unsigned)time(NULL)); // �����Լ�
	system("cls"); //ClearScreen - �ܼ�â�� ���θ� ����� ���(Windows.h)
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

			// �� ��Ȳ����
		if (kbhit()) // ���� Ű�Է��� �Ǿ��ٸ�...
		{
			ch = getch(); // �Է��� Ű���� �޾ƿͼ� ch�� ����
			if (ch == 0xE0 || ch == 0)
			{
				getch();
			}
			else
			{
				switch (ch)
				{
				case ' ': //SpaceBar�� ���� ���...
					if (bx == -1)
					{
						bx = fx;
						by = 23;
					}
					break;
				case ESC: //ESC�� �������...
					goto end;
				}
			}
		}
		// ���� ����
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

				for (;;) // ���ѹݺ�
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
				Enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0])); // ���� ���� Ÿ��  ��ǻ� 5��
				Enemy[i].exist = TRUE; // ���� �����ֱ�
			}
		}
		// �÷��̾� �Ѿ� �̵� �� ���
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
				putch('i'); // �̻���
			}
		}

		// ������ �Ʊ� �Ѿ��� �浹 ����
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

		// ���� �Ѿ� �̵� �� ���
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

		// ���� �Ѿ˰� �÷��̾��� �浹 ����
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

		// ���� �̵� �� ���
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
		printf("���� : %d", score);

		Sleep(20);
	}
end:
	system("cls");
	gotoxy(58, 10);
	printf("GAMEOVER");
	gotoxy(58, 15);
	printf("���� = %d", score);
	CursorView(0);
	getchar();
}
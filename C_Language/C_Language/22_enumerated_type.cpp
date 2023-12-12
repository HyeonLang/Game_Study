// 22_enumerated_type.cpp
/*
	���� 1 : ���� ���� �м�
		- �̹��� �ݿ��ϱ���
		- �� �ڵ带 �м��Ͽ� �ּ� �ޱ�

	���� 2 : ī�� ���� �����
		- ����, ��Ŀ �� �ϳ� �����Ͽ� �����
		- ��Ģ�� ������Ű ����
		- ������ ���� ����������
*/

/*
	������
	- ���� ������ �ִ� ������ ����� �̸��� �ο��ϴ� �ڷ���
	
	- �ڵ��� ������ ��� �� ���������� ����������.

	- ������ ���� �������� ���� ��� �� ���� ���Ҵ� 0, �� ������
	���ҵ��� ���� ���� �ִ� ���Ұ��� + 1�Ǵ� ���� ������.

	- ���ǵ� ���Ҵ� ��ũ�� ����� �����ϰ� ��밡��

	- �������� ������ ���� ��ü�� ���Ҹ����� �����Ӱ� ��밡��
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void enum_();

void mini_rpg();

int main()
{
	//enum_();

	mini_rpg();

	{
		//clock_t prev_time = clock();

		//clock_t cur_time = clock();

		//while (1)
		//{
		//	cur_time = clock();

		//	if (cur_time - prev_time >= 1000)
		//	{
		//		printf("%d\n", clock());
		//		prev_time = clock();
		//	}
		//}

	}

	//{
	//	clock_t prev_time = clock();

	//	clock_t cur_time = clock();

	//	int delta = 0;

	//	int monster_spawn_timer = 0;
	//	int monster_move_timer = 0;

	//	while (1)
	//	{
	//		cur_time = clock();
	//		delta = cur_time - prev_time;
	//		prev_time = cur_time;

	//		if ((monster_spawn_timer += delta) >= 1000)
	//		{
	//			printf("���� ����\n");
	//			monster_spawn_timer -= 1000;
	//		}

	//		if ((monster_move_timer += delta) >= 1500)
	//		{
	//			printf("���� �̵�\n");
	//			monster_move_timer -= 1500;
	//		}
	//	}
	//}

	return 0;
}

void enum_()
{
	{
#define RED 0
#define ORG 1
#define YEL 2

		int c = 0;

		printf("�� �Է� (0 ~ 2)\n");
		scanf_s("%d", &c);

		if (c == RED)
			printf("red\n");

		if (c == ORG)
			printf("orange\n");

		if (c == YEL)
			printf("yellow\n");
		printf("\n");
	}

	{
		enum color
		{
			Min,
			Red = Min,
			Orange,
			Yellow,
			Max
		};

		int c = 0;

		printf("�� �Է� (0 ~ 2)\n");
		scanf_s("%d", &c);

		if (c == Red)
			printf("red\n");

		if (c == Orange)
			printf("orange\n");

		if (c == Yellow)
			printf("yellow\n");
		printf("\n");
		
		for (int i = Min; i < Max; i++)
			;
	}

	{
		// ���� �������� ���� ��� �պ��� 1ū���� ����.
		enum pet { dog, cat = 10, rabbit, hamster };

		printf("dog\t: %d\n", dog);
		printf("cat\t: %d\n", cat);
		printf("rabbit\t: %d\n", rabbit);
		printf("hamster\t: %d\n", hamster);
	}
}

enum Object
{
	BLANK,
	WALL,
	PLAYER,
	MONSTER
};

enum MoveDirection
{
	up		= 'w',
	down	= 's',
	left	= 'a',
	right	= 'd'
};

struct Position
{
	int x;
	int y;
};

struct Monster
{
	Position pos;
	bool is_active;
};

const int map_width = 15;
const int map_height = 20;
int map[map_height][map_width];

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetUp(int map[][map_width], Position* player_position, Monster* monster)
{
	//============================	
	//[�� ����]
	//============================
	 
	// �� ��ġ
	for (int y = 0; y < map_height; y++)
		for (int x = 0; x < map_width; x++)
		{
			if (x == 0 || x == map_width - 1 ||
				y == 0 || y == map_height - 1)
				map[y][x] = WALL;
			else
				map[y][x] = BLANK;
		}

	// �÷��̾� ����
	player_position->x = map_width / 2;
	player_position->y = 1;

	map[player_position->y][player_position->x] = PLAYER;

	// ���� ����
	map[map_height / 2][map_width / 2] = MONSTER;

	monster->is_active = true;
	monster->pos.x = map_width / 2;
	monster->pos.y = map_height / 2;

	//============================	
	//[Ŀ�� �����]
	//============================
	CursorView();

	//============================	
	//[�õ� ����]
	//============================
	srand(time(NULL));
}

void PrintMap(int map[][map_width], int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			switch (map[y][x])
			{
			case BLANK:      printf("  ");   break;
			case WALL:      printf("��");   break;
			case PLAYER:   printf("��");   break;
			case MONSTER:   printf("��");   break;
			} // switch (map[y][x])
		printf("\n");
	}
}

void SwapObject(int map[][map_width], Position pos1, Position pos2)
{
	int temp = map[pos1.y][pos1.x];
	map[pos1.y][pos1.x] = map[pos2.y][pos2.x];
	map[pos2.y][pos2.x] = temp;
}

void MovePlayer(int map[][map_width], Position* player_position, Position move_direction)
{
	Position dest;
	dest.x = player_position->x + move_direction.x;
	dest.y = player_position->y + move_direction.y;

	switch (map[dest.y][dest.x])
	{
	case WALL:
	case PLAYER:
		break;

	case BLANK:
	{
		SwapObject(map, *player_position, dest);
		*player_position = dest;
		break;
	}
	case MONSTER:
	{
		printf("���͸� ����!\n");
		Sleep(1000);
		printf("��Ҵ�!\n");
		Sleep(1000);
		system("cls");

		map[dest.y][dest.x] = BLANK;

		break;
	}
	}
}

void MoveMonster(int map[][map_width], Monster* monster, Position move_direction)
{
	Position dest;
	dest.x = monster->pos.x + move_direction.x;
	dest.y = monster->pos.y + move_direction.y;

	switch (map[dest.y][dest.x])
	{
	case WALL:
	case MONSTER:
		break;

	case BLANK:
	{
		SwapObject(map, monster->pos, dest);
		monster->pos = dest;
		break;
	}

	case PLAYER:
	{
		printf("���͸� ����!\n");
		Sleep(1000);
		printf("��Ҵ�!\n");
		Sleep(1000);
		system("cls");

		map[monster->pos.y][monster->pos.x] = BLANK;
		monster->is_active = false;
		break;
	}
	}
}

void mini_rpg()
{
	Position p_pos;
	Monster monster;

	SetUp(map, &p_pos, &monster);

	clock_t prev_time = clock();

	int move_key = 0;

	while (true)
	{
		gotoxy(0, 0);
		PrintMap(map, map_width, map_height);

		// �÷��̾� �̵�
		if (_kbhit())
		{
			move_key = _getch();

			switch (move_key)
			{
			case up:	MovePlayer(map, &p_pos, Position{ 0, -1 }); break;
			case down:	MovePlayer(map, &p_pos, Position{ 0, 1 }); break;
			case left:	MovePlayer(map, &p_pos, Position{ -1, 0 }); break;
			case right:	MovePlayer(map, &p_pos, Position{ 1, 0 }); break;
			}
		}

		// ���� �̵�
		if (clock() - prev_time >= 1000)
		{
			prev_time = clock();

			if (monster.is_active == true && map[monster.pos.y][monster.pos.x] == MONSTER)
			{
				move_key = rand() % 4;

				switch (move_key)
				{
				case 0: move_key = up; break;
				case 1: move_key = down; break;
				case 2: move_key = left; break;
				case 3: move_key = right; break;
				}

				switch (move_key)
				{
				case up:	MoveMonster(map, &monster, Position{ 0, -1 }); break;
				case down:	MoveMonster(map, &monster, Position{ 0, 1 }); break;
				case left:	MoveMonster(map, &monster, Position{ -1, 0 }); break;
				case right:	MoveMonster(map, &monster, Position{ 1, 0 }); break;
				}
			}
			else
				monster.is_active = false;
		}

	}
}
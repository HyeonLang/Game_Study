// 22_enumerated_type.cpp
/*
	과제 1 : 빙고 게임 분석
		- 이번주 금요일까지
		- 각 코드를 분석하여 주석 달기

	과제 2 : 카드 게임 만들기
		- 섯다, 포커 중 하나 선택하여 만들기
		- 규칙은 나무위키 참고
		- 다음주 수업 시작전까지
*/

/*
	열거형
	- 서로 관련이 있는 정수형 상수에 이름을 부여하는 자료형
	
	- 코드의 가독성 향상 및 유지보수가 용이해진다.

	- 원소의 값을 지정하지 않을 경우 맨 앞의 원소는 0, 그 이후의
	원소들은 본인 앞의 있는 원소값에 + 1되는 값을 가진다.

	- 정의된 원소는 매크로 상수와 동일하게 사용가능

	- 열거형을 선언한 지역 전체에 원소명으로 자유롭게 사용가능
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
	//			printf("몬스터 스폰\n");
	//			monster_spawn_timer -= 1000;
	//		}

	//		if ((monster_move_timer += delta) >= 1500)
	//		{
	//			printf("몬스터 이동\n");
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

		printf("값 입력 (0 ~ 2)\n");
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

		printf("값 입력 (0 ~ 2)\n");
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
		// 값을 지정하지 않은 경우 앞보다 1큰수가 들어간다.
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
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetUp(int map[][map_width], Position* player_position, Monster* monster)
{
	//============================	
	//[맵 세팅]
	//============================
	 
	// 벽 설치
	for (int y = 0; y < map_height; y++)
		for (int x = 0; x < map_width; x++)
		{
			if (x == 0 || x == map_width - 1 ||
				y == 0 || y == map_height - 1)
				map[y][x] = WALL;
			else
				map[y][x] = BLANK;
		}

	// 플레이어 세팅
	player_position->x = map_width / 2;
	player_position->y = 1;

	map[player_position->y][player_position->x] = PLAYER;

	// 몬스터 세팅
	map[map_height / 2][map_width / 2] = MONSTER;

	monster->is_active = true;
	monster->pos.x = map_width / 2;
	monster->pos.y = map_height / 2;

	//============================	
	//[커서 숨기기]
	//============================
	CursorView();

	//============================	
	//[시드 세팅]
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
			case WALL:      printf("※");   break;
			case PLAYER:   printf("☆");   break;
			case MONSTER:   printf("●");   break;
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
		printf("몬스터를 만남!\n");
		Sleep(1000);
		printf("잡았다!\n");
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
		printf("몬스터를 만남!\n");
		Sleep(1000);
		printf("잡았다!\n");
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

		// 플레이어 이동
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

		// 몬스터 이동
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
#include "SnakeHead.h"
#include "utility.h"
#include <string>

SnakeHead::SnakeHead()
{
	Init(20, 20);
}

SnakeHead::~SnakeHead()
{
	Destroy();
}

void SnakeHead::Init(int x, int y)
{
	curr_dir = Direction::UNKNOWN;
	SetPosition(x, y);
	

	next_position.x = x;
	next_position.y = y - 1;
	pre_position.x = x;
	pre_position.y = y - 1;
}

void SnakeHead::Render()
{

	switch (curr_dir) {
	case  Direction::DIR_R: gotoxy(position.x * 2, position.y, "▶"); break;
	case  Direction::DIR_L:	gotoxy(position.x * 2, position.y, "◀"); break;
	case  Direction::DIR_U: gotoxy(position.x * 2, position.y, "▲"); break;
	case  Direction::DIR_D: gotoxy(position.x * 2, position.y, "▼"); break;
	}

	/*switch (curr_dir) {
	case  Direction::DIR_R: std::cout << "▶"; break;
	case  Direction::DIR_L: std::cout << "◀"; break;
	case  Direction::DIR_U: std::cout << "▲"; break;
	case  Direction::DIR_D: std::cout << "▼"; break;
	}*/


	
}

void SnakeHead::Destroy()
{
}

void SnakeHead::UpdateHead(int delta)
{
	if (_kbhit()) {
		if (_getch() == 224)//224면 특수문자 : 한번 더 받음
			_getch();

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) curr_dir = Direction::DIR_R;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) curr_dir = Direction::DIR_L;
		if (GetAsyncKeyState(VK_UP) & 0x8000) curr_dir = Direction::DIR_U;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) curr_dir = Direction::DIR_D;

	}

	switch (curr_dir)
	{
	case Direction::UNKNOWN: break;
	case Direction::DIR_R: next_position.x = position.x + 1; break;
	case Direction::DIR_L: next_position.x = position.x - 1; break;
	case Direction::DIR_U: next_position.y = position.y - 1; break;
	case Direction::DIR_D: next_position.y = position.y + 1; break;
	}


}

#include "Monster.h"
#include "utility.h"

Monster::Monster()
{
	Init();
}

Monster::~Monster()
{
	Destroy();
}

void Monster::Init()
{
	position = Point(0, 0);
	curr_dir = Monster::Direction::UNKNOWN;
	is_active = false;
	move_timer_ms = 0;
	move_interval_ms = 100;
}

void Monster::Update(int delta)
{
	move_timer_ms += delta;

	if (move_timer_ms >= move_interval_ms)
	{
		switch (curr_dir)
		{
		case Monster::Direction::UNKNOWN: break;
		case Monster::Direction::DIR_R: position.x++; break;
		case Monster::Direction::DIR_L: position.x--; break;
		case Monster::Direction::DIR_U: position.y--; break;
		case Monster::Direction::DIR_D: position.y++; break;
		}

		move_timer_ms = 0;
	}
}

void Monster::Render()
{
	gotoxy(position.x * 2, position.y);
	std::cout << "бс";
}

void Monster::Destroy()
{
	position = Point(0, 0);
	curr_dir = Monster::Direction::UNKNOWN;
	is_active = false;
	move_timer_ms = 0;
	move_interval_ms = 100;
}

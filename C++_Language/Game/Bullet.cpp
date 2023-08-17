#include "Bullet.h"
#include"utility.h"

Bullet::Bullet()
{
	Init();
}

Bullet::~Bullet()
{
	Destroy();
}

void Bullet::Init()
{
	position = Point(0, 0);
	curr_dir = Bullet::Direction::UNKNOWN;
	is_active = false;
	move_timer_ms = 0;
	move_interval_ms = 100;
}

void Bullet::Update(int delta)
{
	move_timer_ms += delta;

	if (move_timer_ms >= move_interval_ms)
	{
		switch (curr_dir)
		{
		case Bullet::Direction::UNKNOWN: break;
		case Bullet::Direction::DIR_R: position.x++; break;
		case Bullet::Direction::DIR_L: position.x--; break;
		case Bullet::Direction::DIR_U: position.y--; break;
		case Bullet::Direction::DIR_D: position.y++; break;
		}

		move_timer_ms = 0;
	}
}

void Bullet::Render()
{
	gotoxy(position.x * 2, position.y);

	switch (curr_dir)
	{
	case Bullet::Direction::UNKNOWN: break;
	case Bullet::Direction::DIR_R: std::cout << "กๆ"; break;
	case Bullet::Direction::DIR_L: std::cout << "ก็"; break;
	case Bullet::Direction::DIR_U: std::cout << "ก่"; break;
	case Bullet::Direction::DIR_D: std::cout << "ก้"; break;
	}
}

void Bullet::Destroy()
{
	position = Point(0, 0);
	curr_dir = Bullet::Direction::UNKNOWN;
	is_active = false;
	move_timer_ms = 0;
	move_interval_ms = 100;
}

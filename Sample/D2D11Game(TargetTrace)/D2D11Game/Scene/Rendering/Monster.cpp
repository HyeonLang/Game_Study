#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
	stopwatch.Start();
}

Monster::~Monster()
{
}

void Monster::Event()
{
	restore_stopwatch.Start();
	is_intersect = true;
	is_active = false;

}

void Monster::Move()
{
	return;

	switch (direction)
	{
	case Direction::Up:		position.y++; break;
	case Direction::Right:	position.x++; break;
	case Direction::Down:	position.y--; break;
	case Direction::Left:	position.x--; break;
	}

	if (stopwatch.GetElapsedTimeMs() >= 1500)
	{
		Direction new_dir = static_cast<Direction>(Math::Random(0, 3));

		if (direction == new_dir)
		{
			int dir_num = static_cast<int>(new_dir);
			dir_num = (dir_num <= 1) ? dir_num + 2 : dir_num - 2;

			direction = static_cast<Direction>(dir_num);
		}
		else
			direction = new_dir;

		stopwatch.Start();
	}

	auto half_width = Settings::Get().GetWidth() * 0.5;
	auto half_height = Settings::Get().GetHeight() * 0.5;
	auto half_scale_x = scale.x * 0.5;
	auto half_scale_y = scale.y * 0.5;

	if (position.x + half_scale_x > half_width) direction = Direction::Left;
	if (position.x - half_scale_x < -half_width) direction = Direction::Right;
	if (position.y + half_scale_y > half_height) direction = Direction::Down;
	if (position.y - half_scale_y < -half_height) direction = Direction::Up;
}

void Monster::Restore()
{
	if (is_intersect != true) return;
	if (restore_stopwatch.GetElapsedTimeMs() <= 900) return;

	is_intersect = false;
	is_active = true;

	float half_width = Settings::Get().GetWidth() * 0.5;
	float half_height = Settings::Get().GetHeight() * 0.5;
	float half_scale_x = scale.x * 0.5;
	float half_scale_y = scale.y * 0.5;

	position.x = Math::Random(-half_width + half_scale_x, half_width - half_scale_x);
	position.x = Math::Random(-half_height + half_scale_y, half_height - half_scale_y);

}

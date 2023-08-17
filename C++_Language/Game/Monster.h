#pragma once
#include"Point.h"
typedef long clock_t;

class Monster
{
public:
	enum class Direction
	{
		UNKNOWN,
		DIR_R,
		DIR_L,
		DIR_U,
		DIR_D,
	};

public:
	Monster();
	~Monster();

	void Init();
	void Update(int delta);
	void Render();
	void Destroy();

	const Point& GetPosition() const { return position; }

	void SetPosition(const Point& position) { this->position = position; }
	void SetPosition(const int& x, const int& y) { this->position = Point(x, y); }

	void SetActive(const bool& b) { is_active = b; }
	bool IsActive() { return is_active; }

	void SetMoveIntervalMS(const clock_t& ms) { move_interval_ms = ms; }

	void SetDirection(const Direction& dir) { curr_dir = dir; }

private:
	Point position;
	Direction curr_dir;
	bool is_active = false;

	clock_t move_timer_ms = 0;
	clock_t move_interval_ms = 100;
};


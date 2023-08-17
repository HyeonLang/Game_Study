#pragma once
#include "Snake.h"

class SnakeHead : public Snake
{
public:
	enum class Direction {
		UNKNOWN,
		DIR_R,
		DIR_L,
		DIR_U,
		DIR_D,
	};
public:
	SnakeHead();
	~SnakeHead();
	void Init(int x = 0, int y = 0);
	//void Update(int delta);
	void Render();
	void Destroy();
	void UpdateHead(int delta);
	void SetDirection(const Direction& dir) { curr_dir = dir; }
private:
	Direction curr_dir;
};


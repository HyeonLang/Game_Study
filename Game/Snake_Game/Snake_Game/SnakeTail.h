#pragma once
#include "Snake.h"
class SnakeTail : public Snake
{
public:
	SnakeTail(int x = 0 , int y = 0);
	~SnakeTail();
	void Init(int x = 0, int y = 0);
	//void Update(int delta);
	void Render();
	void Destroy();


private:
};


#include "SnakeTail.h"
#include "utility.h"


SnakeTail::SnakeTail(int x, int y)
{
	Init(x, y);
}

SnakeTail::~SnakeTail()
{
	Destroy();
}
void SnakeTail::Init(int x, int y)
{
	position.x = x;
	position.y = y;

	next_position.x = x;
	next_position.y = y;

	pre_position.x = x;
	pre_position.y = y;
}


void SnakeTail::Render()
{
	gotoxy(position.x * 2, position.y, "бс");

	//std::cout << "бс";
}

void SnakeTail::Destroy()
{
}

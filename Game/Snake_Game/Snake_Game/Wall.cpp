#include "wall.h"

Wall::Wall(Point p)
{
	Init(p.x, p.y);
}

Wall::Wall(int x, int y)
{
	Init(x, y);
}

Wall::~Wall()
{
	Destroy();
}

void Wall::Init(int x, int y)
{
	position.x = x;
	position.y = y;
}

void Wall::Update(int delta)
{
}

void Wall::Render()
{
	gotoxy(position.x * 2, position.y, "¡Ø");
	//std::cout << "¡Ø";
}

void Wall::Destroy()
{
	position.x = 0;
	position.y = 0;
}

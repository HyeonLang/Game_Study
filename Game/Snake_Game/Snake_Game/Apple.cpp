#include "Apple.h"

Apple::Apple()
{
	Init();
}

Apple::~Apple()
{
	Destroy();
}

void Apple::Init()
{
	position = Point(0, 0);
	duration_time_ms = 0;
	isActive = false;
	limit_time_ms = 10000;
}

void Apple::Update(int delta)
{

	duration_time_ms += delta;
	
	if (duration_time_ms >= limit_time_ms) {
		isActive = false;
	}
}

void Apple::Render()
{
	gotoxy(position.x * 2, position.y, "£À");
	//std::cout << "£À";
}

void Apple::Destroy()
{
	position = Point(0, 0);
	duration_time_ms = 0;
	isActive = false;
}

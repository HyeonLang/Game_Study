#include "Snake.h"

void Snake::Update(int delta)
{
	pre_position.x = position.x;
	pre_position.y = position.y;

	position.x = next_position.x;
	position.y = next_position.y;

}

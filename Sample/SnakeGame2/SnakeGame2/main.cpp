// main.cpp

#include"stdafx.h"

int main()
{
	SnakeGame game;

	game.Initialize();

	bool b = true;
	while (b)
	{
		b = game.Update();
		game.Render();
	}

	return 0;
}
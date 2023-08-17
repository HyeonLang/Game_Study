#pragma once
#include"utility.h"
#include"Snake.h"
#include"Wall.h"
#include"Item.h"
class SnakeGame {
public:
	void Init();
	void Update(int delta);
	void Render();
	void Destroy();
	
	bool const IsGameOver() { return game_over; }
private:
	clock_t move_timer_ms = 0;
	clock_t move_interval_ms = 80;
	bool game_over = false;

	std::vector<Snake*> snake;
	Item* item[20];
	std::vector<Wall*> wall;
};


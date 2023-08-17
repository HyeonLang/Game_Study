#include "SnakeGame.h"
#include "utility.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "Apple.h"


//bool operator==(const Snake& s, const Wall& w)
//{
//	return s.GetPosition() == w.GetPosition();
//}
//
//bool operator==(const Snake& s, const Item& i)
//{
//	return s.GetPosition() == i.GetPosition();
//}


void SnakeGame::Init()
{
	game_over = false;
	int map_size = MAP_SIZE;
	for (int x = 0; x < (map_size + 1); x++) {
		wall.push_back(new Wall(x, 0)); 
		wall.push_back(new Wall(x, map_size));
	}
	for (int y = 1; y < map_size; y++) {
		wall.push_back(new Wall(0, y));
		wall.push_back(new Wall(map_size, y));
	}

	snake.push_back(new SnakeHead);


	for (int i = 0; i < 20; i++) {
		item[i] = new Apple;
	}
	
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));
}

void SnakeGame::Update(int delta)
{
	move_timer_ms += delta;
	static_cast<SnakeHead*>(snake[0])->UpdateHead(delta);
	for (auto i : item) {
		if (i->GetIsActive()) i->Update(delta);
	}
	if (move_timer_ms >= move_interval_ms) {

		for (int s = 0; s < snake.size(); s++) {
			snake[s]->Update(delta);
		}
		
		int item_range = MAP_SIZE - 1;
		for (auto i : item) {
			if (rand() % 300 == 0 && !i->GetIsActive()) {
				i->Init();
				i->SetIsActive(true);
				i->SetPosition((rand() % item_range) + 1, (rand() % item_range) + 1);
			}
		}


		move_timer_ms = 0;
	}
	
	for (auto w : wall) {
		if (snake.at(0)->GetPosition() == w->GetPosition()) {
			game_over = true;
		}
	}

	for (auto i : item) {
		if (snake.at(0)->GetPosition() == i->GetPosition() && i->GetIsActive()) {

			i->SetIsActive(false);

			Point new_tail_pos = snake.at(snake.size() - 1)->GetPosition();
			snake.push_back(new SnakeTail(new_tail_pos.x, new_tail_pos.y));
		}
	}

	for (int s = 1; s < snake.size(); s++) {
		snake[s]->SetNextPosition(snake[s - 1]->GetPosition());
	}
}


void SnakeGame::Render()
{
	//system("cls"); //화면을 지우는 코드
	
	ScreenClear();

	for (auto w : wall) {
		w->Render();
	}

	for (auto i : item) {
		if (i->GetIsActive()) i->Render();
	}	
	for (auto s : snake) {
		s->Render();
	}

	ScreenFlipping();
}

void SnakeGame::Destroy()
{
	for (auto s : snake) {
		SAFE_DELETE(s);
	}
	SAFE_DELETE_ARRAY(*item);
	for (auto w : wall) {
		SAFE_DELETE(w);
	}
}



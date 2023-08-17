#include"utility.h"
#include"SnakeGame.h"

int main() {
	SnakeGame s;
	
	clock_t prev_time = clock();
	clock_t current_time = clock();

	ScreenInit();

	s.Init();
	while (true)
	{
		current_time = clock();

		s.Update(current_time - prev_time);
		s.Render();
		if (s.IsGameOver()) break;

		prev_time = current_time;
	}
	s.Destroy();
}

#include"utility.h"
#include"ShootGame.h"

int main()
{
	ShootGame s;

	clock_t prev_time = clock();
	clock_t current_time = clock();

	s.Init();
	while (true)
	{
		current_time = clock();
		
		s.Update(current_time - prev_time);
		s.Render();

		prev_time = current_time;
	}
	s.Destroy();


	return 0;
}
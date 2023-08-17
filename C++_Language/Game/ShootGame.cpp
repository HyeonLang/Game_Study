#include "ShootGame.h"
#include "utility.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"

bool operator==(const Bullet& b, const Monster& m)
{
	return b.GetPosition() == m.GetPosition();
}

void ShootGame::Init()
{
	player = new Player;
	player->SetPosition(20, 10);

	monsters = new Monster[monster_size];

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));
}

void ShootGame::Update(int delta)
{
	player->Update(delta);

	for (int i = 0; i < monster_size; i++)
		if (monsters[i].IsActive())
		{
			monsters[i].Update(delta);

			if (monsters[i].GetPosition().y > 30)
			{
				monsters[i].Destroy();
				monster_count--;
			}
		}

	spawn_monster_timer_ms += delta;
	if (spawn_monster_timer_ms >= spawn_monster_interval_ms && monster_count < monster_size)
	{
		for (int i = 0; i < monster_size; i++)
		{
			if (monsters[i].IsActive() == true)
				continue;
			monsters[i].Init();

			monsters[i].SetActive(true);
			monsters[i].SetPosition(rand() % 30 ,1);
			monsters[i].SetDirection(Monster::Direction::DIR_D);
			monster_count++;
			break;
		}

		spawn_monster_timer_ms = 0;
	}

	auto bullets = player->GetBullets();
	for (int i = 0; i < 10; i++)
	{
		if (bullets[i].IsActive() == false)
			continue;

		for (int j = 0; j < monster_size; j++)
		{
			if (monsters[i].IsActive() == false)
				continue;

			if (bullets[i] == monsters[j])
			{
				bullets[i].Destroy();
				monsters[j].Destroy();
				monster_count--;
				player->bullet_count--;
			}
		}
	}
}

void ShootGame::Render()
{
	system("cls"); //화면을 지우는 코드
	player->Render();

	for (int i = 0; i < monster_size; i++)
		if (monsters[i].IsActive())
		{
			monsters[i].Render();
		}

	Sleep(10);
}

void ShootGame::Destroy()
{
	SAFE_DELETE(player);
	SAFE_DELETE_ARRAY(monsters);
}

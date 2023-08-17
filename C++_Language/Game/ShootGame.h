#pragma once

/*
	슈팅 게임

	플레이어가 움직이면서 아래로 내려오는 적을
	쓰러트리는 게임

	플레이어(이동, 쏘기)
	몬스터(이동)
	총알(이동)

	충돌 처리
*/


constexpr int monster_size = 20;
typedef long clock_t;

class ShootGame
{
public:
	void Init();
	void Update(int delta);
	void Render();
	void Destroy();

private:
	class Player* player;

	class Monster* monsters;
	int monster_count = 0;

	clock_t spawn_monster_timer_ms = 0;
	clock_t spawn_monster_interval_ms = 300;
};


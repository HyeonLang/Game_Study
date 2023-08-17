#pragma once

/*
	���� ����

	�÷��̾ �����̸鼭 �Ʒ��� �������� ����
	����Ʈ���� ����

	�÷��̾�(�̵�, ���)
	����(�̵�)
	�Ѿ�(�̵�)

	�浹 ó��
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


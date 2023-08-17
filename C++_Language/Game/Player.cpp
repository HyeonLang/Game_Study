#include "Player.h"
#include "utility.h"

Player::Player()
	: position(0, 0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	position.x = 0;
	position.y = 0;
}

void Player::Update(int delta)
{
	if (_kbhit()) // ��� Ű�Է��� �ް� �Ǹ�
	{
		if (_getch() == 224) //224�� Ư������ : �ѹ� �� ����
			_getch();

		// MOVE
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) position.x++;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) position.x--;
		if (GetAsyncKeyState(VK_UP) & 0x8000) position.y--;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) position.y++;

		// SHOOT
		if (GetAsyncKeyState('Z') & 0x8000) Shoot();
	}

	for (auto& bullet : bullets)
		if (bullet.IsActive())
		{
			bullet.Update(delta);

			if (bullet.GetPosition().y < 0)
			{
				bullet.Destroy();
				bullet_count--;
			}
		}
}

void Player::Render()
{
	gotoxy(position.x * 2, position.y); //2byte ���� ���
	std::cout << "��";

	for (auto& bullet : bullets)
		if (bullet.IsActive())
			bullet.Render();
}

void Player::Destroy()
{
}

void Player::Shoot()
{
	if (bullet_count >= bullet_size)  return;

	for (auto& bullet : bullets)
	{
		if (bullet.IsActive() == true)
			continue;
		bullet.Init();

		bullet.SetActive(true);
		bullet.SetPosition(position.x, position.y - 1);
		bullet.SetDirection(Bullet::Direction::DIR_U);
		bullet_count++;

		return;
	}
}


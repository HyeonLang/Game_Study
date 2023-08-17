#include "stdafx.h"
#include "Player.h"

Player::Player(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
}

Player::~Player()
{
}

void Player::Move()
{
	if (GetAsyncKeyState('W') & 0x8000) position.y += speed;
	if (GetAsyncKeyState('S') & 0x8000) position.y -= speed;
	if (GetAsyncKeyState('D') & 0x8000) position.x += speed;
	if (GetAsyncKeyState('A') & 0x8000) position.x -= speed;
}

void Player::Restore()
{
	if (is_intersect != true) return;
	if (restore_stopwatch.GetElapsedTimeMs() <= 900) return;

	intersect_color = D3DXCOLOR(1, 1, 1, 1);
	speed = 3.0f;
	is_intersect = false;
}

void Player::Event()
{
	restore_stopwatch.Start();
	intersect_color = D3DXCOLOR(1, 0, 0, 1);
	is_intersect = true;
	//speed *= 0.1;
}

#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	pos = { WINSIZE_X / 2 , WINSIZE_Y - 30 };
	speed = 1;
}

void Player::Update()
{
    /*
        GetAsyncKeyState() : 호출된 시점의 키 입력 상태를 확인하는 함수

        옵션
        0x0001 : 이전에 누른적이 있는가
        0x8000 : 호출시점에 눌려있는가?

        0x0000 : 이전에 누른적이 없고 호출시점에도 눌려 있지 않음
        0x0001 : 이전에 누른적이 있고 호출시점에는 눌려 있지 않음
        0x8000 : 이전에 누른적이 없고 호출시점에는 눌려있음
        0x8001 : 이전에 누른적이 있고 호출시점에도 눌려있음
    */

    if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
        if (box.left >= speed) pos.x -= speed;

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
        if (box.right <= WINSIZE_X - speed) pos.x += speed;

    box = RECT_MAKE(pos.x, pos.y, 50);
}

void Player::Render()
{
    RECT_DRAW(box);
}

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
        GetAsyncKeyState() : ȣ��� ������ Ű �Է� ���¸� Ȯ���ϴ� �Լ�

        �ɼ�
        0x0001 : ������ �������� �ִ°�
        0x8000 : ȣ������� �����ִ°�?

        0x0000 : ������ �������� ���� ȣ��������� ���� ���� ����
        0x0001 : ������ �������� �ְ� ȣ��������� ���� ���� ����
        0x8000 : ������ �������� ���� ȣ��������� ��������
        0x8001 : ������ �������� �ְ� ȣ��������� ��������
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

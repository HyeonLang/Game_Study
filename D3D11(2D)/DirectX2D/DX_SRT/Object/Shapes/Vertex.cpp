#include"pch.h"


float ratio_pos_x(int pos_x)
// �Է��� ������ǥ�� DirectX���� �� �� �ִ� �����ǥ�� ��ȯ���ִ� �Լ�
// ������ �̷��� �ӽ÷� �������� ���߿� ���� ���� �߿� �̸� ��ü�ϴ� ����� �ٷ� ����
{
    float ratio;

        ratio = ((float)pos_x - WIN_CENTER_X) 
            / (float)WIN_CENTER_X;


    return ratio;
}

float ratio_pos_y(int pos_y)
{
    float ratio;

        ratio = ((float)pos_y - WIN_CENTER_Y) / (float)WIN_CENTER_Y;

    return ratio;
}

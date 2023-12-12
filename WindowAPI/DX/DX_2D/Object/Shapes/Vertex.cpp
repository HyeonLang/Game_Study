#include "pch.h"
#include "Vertex.h"

float calc_ratio_pos_x(int pos_x, int mode)   // �Է��� x��ǥ�� -1.0f ~ 1.0f�� ��ȯ
{
    // mode = 0 : ���� �ϴ� ����, mode = 1 : �߾� ����
    float ratio;

    switch (mode) {
    case 0:
        ratio = ((float)pos_x - WIN_CENTER_X) / WIN_CENTER_X;
        break;
    case 1:
    default:
        ratio = (float)pos_x / WIN_CENTER_X;
        break;
    }


    return ratio;
}

float calc_ratio_pos_y(int pos_y, int mode)   // �Է��� y��ǥ�� -1.0f ~ 1.0f�� ��ȯ
{
    // mode = 0 : ���� �ϴ� ����, mode = 1 : �߾� ����
    float ratio;

    switch (mode) {
    case 0:
        ratio = ((float)pos_y - WIN_CENTER_Y) / WIN_CENTER_Y;
        break;
    case 1:
    default:
        ratio = (float)pos_y / WIN_CENTER_Y;
        break;
    }
    return ratio;
}
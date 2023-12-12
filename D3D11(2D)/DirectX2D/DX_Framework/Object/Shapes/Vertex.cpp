#include"pch.h"


float ratio_pos_x(int pos_x)
// 입력한 절대좌표를 DirectX에서 쓸 수 있는 상대좌표로 변환해주는 함수
// 지금은 이렇게 임시로 만들지만 나중에 나갈 내용 중에 이를 대체하는 기능을 다룰 예정
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

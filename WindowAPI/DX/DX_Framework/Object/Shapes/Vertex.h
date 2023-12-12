#pragma once
//#include"framework.h"
struct Vertex
{
    Float3 position;
    Float4 colour;
    // 각각 정점의 위치, 색을 기록할 실수의 묶음들

    Vertex() // 정점을 아무런 입력 없이 디폴트로 선언했을 때의 초기화값
    {
        position = Float3(0, 0, 0);
        colour = Float4(0, 0, 0, 1);
    }
    Vertex(float x, float y, float r, float g, float b) // 값을 포함해서 초기화하는 생성자
    {
        position = Float3(x, y, 0);
        colour = Float4(r, g, b, 1);
    }
};


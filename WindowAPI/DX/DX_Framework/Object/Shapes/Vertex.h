#pragma once
//#include"framework.h"
struct Vertex
{
    Float3 position;
    Float4 colour;
    // ���� ������ ��ġ, ���� ����� �Ǽ��� ������

    Vertex() // ������ �ƹ��� �Է� ���� ����Ʈ�� �������� ���� �ʱ�ȭ��
    {
        position = Float3(0, 0, 0);
        colour = Float4(0, 0, 0, 1);
    }
    Vertex(float x, float y, float r, float g, float b) // ���� �����ؼ� �ʱ�ȭ�ϴ� ������
    {
        position = Float3(x, y, 0);
        colour = Float4(r, g, b, 1);
    }
};


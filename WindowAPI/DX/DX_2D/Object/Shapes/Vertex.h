#pragma once
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

// ��ǥ ���� ó��
float calc_ratio_pos_x(int pos_x, int mode);   // �Է��� x��ǥ�� -1.0f ~ 1.0f�� ��ȯ
float calc_ratio_pos_y(int pos_y, int mode);   // �Է��� y��ǥ�� -1.0f ~ 1.0f�� ��ȯ

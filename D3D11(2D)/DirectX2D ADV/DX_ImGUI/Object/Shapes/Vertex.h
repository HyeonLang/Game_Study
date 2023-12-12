#pragma once
struct Vertex
// ������ �츮�� ������ ���� �� �� ������ ������ �� ����ü�� ���ؼ� ������
{
	Float3 position;
	Float4 colour;

	Vertex()
		// C++���� ����ü�� ��ǻ� public�� �����ϴ� Ŭ������ �ٸ� �� �����Ƿ�
		// �̷��� �����ڸ� ����� �͵� ���� ����

		// ������ �ƹ� �Է� ���� ����Ʈ�� �������� ���� �ʱ�ȭ��
	{
		position = Float3(0, 0, 0);
		colour = Float4(0, 0, 0, 1);
		// 4��° ���� ���İ� - ������ ����� ���� ���� 1�� ���дٴ� �͸� ����� ��
	}
	Vertex(float x, float y, float r, float g, float b)
	{
		position = Float3(x, y, 0);
		colour = Float4(r, g, b, 1);
	}
};

struct VertexPos
{
	Float3 position;

	VertexPos() : position(0, 0, 0) {};
	VertexPos(float x, float y) { position = Float3(x, y, 0); }
}; 

float ratio_pos_x(int pos_x);
float ratio_pos_y(int pos_y);
// �� �� �Լ���
// ������ â�� ������ǥ�� �����ǥ�� ��ȯ�ϴ� �Լ�

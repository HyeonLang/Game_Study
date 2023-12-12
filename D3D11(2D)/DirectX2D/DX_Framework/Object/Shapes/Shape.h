#pragma once
class Shape
{
protected:
	vector<Vertex> verticies = {};
	// vector�� �̿��� �� ������ ����� ������ ����
	float pos_x, pos_y;
	// ������ ��ġ�� ����ص� ����
	ID3D11Buffer* VB;
	// ���� ������ �׷��� ��¿� �ʿ��� �����͸� �˾Ƽ� �����صε��� ���۸� �� ��ü�� ����� ����

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; };
	int GetVertexSize() { return verticies.size(); };
};
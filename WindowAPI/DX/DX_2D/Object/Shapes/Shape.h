#pragma once
#include "Vertex.h"

class Shape
{
protected:
	vector<Vertex> verticies = {};	// vector�� �̿��� �� ������ ����� ������ ����
	float pos_x, pos_y;				// ������ ��ġ ��� ����
	ID3D11Buffer* VB;				// ������ ���� ȭ�鿡 ����ϴ� �� ����� �޸𸮸� ���� ����

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return verticies.size(); }

};


#pragma once
#include "Vertex.h"
class Triangles : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// �ﰢ���� DX���� �׸� �� � ���� �ﰢ�������� �� �������� ���� �����Ѵ�

public:
	Triangles(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t);
	~Triangles();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};


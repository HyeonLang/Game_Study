#pragma once
#include "Vertex.h"
class Triangles : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// 삼각형을 DX에서 그릴 때 어떤 식의 삼각형인지를 이 열거형을 통해 정의한다

public:
	Triangles(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t);
	~Triangles();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};


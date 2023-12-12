#pragma once
#include "Vertex.h"

class Shape
{
protected:
	vector<Vertex> verticies = {};	// vector를 이용해 이 도형이 사용할 정점을 저장
	float pos_x, pos_y;				// 도형의 위치 기록 변수
	ID3D11Buffer* VB;				// 도형을 실제 화면에 출력하는 데 사용할 메모리를 담은 버퍼

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; }
	int GetVertexSize() { return verticies.size(); }

};


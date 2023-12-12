#pragma once
class Shape
{
protected:
	vector<Vertex> verticies = {};
	// vector를 이용해 이 도형이 사용할 정점을 저장
	float pos_x, pos_y;
	// 도형의 위치를 기록해둘 변수
	ID3D11Buffer* VB;
	// 도형 각각이 그래픽 출력에 필요한 데이터를 알아서 저장해두도록 버퍼를 각 객체가 멤버로 보유

public:
	Shape(float x, float y);
	~Shape();

	ID3D11Buffer** const GetBuffer() { return &VB; };
	int GetVertexSize() { return verticies.size(); };
};
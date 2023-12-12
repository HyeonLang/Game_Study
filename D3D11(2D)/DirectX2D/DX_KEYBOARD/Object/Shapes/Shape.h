#pragma once
class Shape
{
protected:
	vector<Vertex> verticies = {};
	// vector를 이용해 이 도형이 사용할 정점을 저장
	float pos_x, pos_y;
	// 도형의 위치를 기록해둘 변수
	VertexBuffer* VB;
	// 도형 각각이 그래픽 출력에 필요한 데이터를 알아서 저장해두도록 버퍼를 각 객체가 멤버로 보유
	// 직접 구현한 클래스 이용

	VertexShader* VS;
	PixelShader* PS;
	// 각 오브젝트 마다 독립된 셰이더를 가진다.

	ColourBuffer* CB;
	// 픽셀 셰이더에 입력할 색 기록 버퍼
	// 각 정점에 색을 입력하여 픽셀 셰이더에서 처리하던 기존 방식에서 
	// 도형 자체 색 정보를 이 버퍼에 기록, 픽셀 셰이더에 넘겨 처리

	// 사용자 정의 클래스 정의하여 사용
public:
	Shape(float x, float y);
	~Shape();
	

	VertexBuffer** const GetBuffer() { return &VB; };
	int GetVertexSize() { return verticies.size(); };
	virtual void Render() = 0;
	// 모든 오브젝트들이 자기자신을 출력하는 기능 함수 : 상속하는 오브젝트 클래스에게 출력하는 기능을 구현하도록 강제

	void SetColor(Float4 colour)	// 색 버퍼에 색을 저장하는 함수
	{
		CB->data.colour = colour;
	}
};
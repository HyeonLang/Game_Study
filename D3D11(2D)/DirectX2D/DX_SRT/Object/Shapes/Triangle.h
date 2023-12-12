#pragma once
class Triangle : public Shape
{
private :
	D3D11_PRIMITIVE_TOPOLOGY type;
	// D3D11_PRIMITIVE_TOPOLOGY는 열거형이므로
	// 해당 타입을 아예 본 클래스에 멤버 변수로 저장해둔다

public:
	Triangle(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t);
	~Triangle();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	// 출력할 때 시스템에 어떤 도형을 그릴 것이지 미리 설정해주는 부분에
	// 이 클래스 객체가 보유한 타입을 입력해야 하기 때문에 이에 접근할 접근자가 필요한 것
};
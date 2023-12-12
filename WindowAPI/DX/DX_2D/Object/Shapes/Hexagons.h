#pragma once
// 클래스 이름이 다은 클래스나 함수와 중복되지 않도록 주의

class Hexagons : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// 육각형을 DX에서 그릴 때 어떤 식의 육각형인지를 이 열거형을 통해 정의한다

public:
	Hexagons(float x, float y, float size,  D3D11_PRIMITIVE_TOPOLOGY t);
	~Hexagons();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};


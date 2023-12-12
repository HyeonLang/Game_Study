#pragma once
class Hexagon : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	Hexagon(int x, int y, float size, D3D11_PRIMITIVE_TOPOLOGY t);
	~Hexagon();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }

};
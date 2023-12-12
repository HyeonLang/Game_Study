#pragma once
class Circle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	float radius;
	float angle;

public:
	Circle(Float2 pos, float size, float angle, D3D11_PRIMITIVE_TOPOLOGY t, int vx_count);
	~Circle();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Render();
};


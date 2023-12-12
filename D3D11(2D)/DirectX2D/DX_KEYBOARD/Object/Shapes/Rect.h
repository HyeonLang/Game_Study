#pragma once
class Rect : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	Rect(Float2 pos, D3D11_PRIMITIVE_TOPOLOGY t);
	~Rect();
	
	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Render();

};


#pragma once
class Box : public Transform
{
private:
	Rect* rect;
public:
	Box(Float2 p, Float2 s, float a, 
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Box();

	void Update(Matrix* parent = NULL);
	void Render();

	void SetColor(Float4 colour)
	{
		rect->SetColor(colour);
	}

};


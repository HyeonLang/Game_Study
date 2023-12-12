#pragma once
class Box : public Transform
{
private:
	Rect* rect;
public:
	Box(Float2 p, Float2 s, float a, 
		D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Box();

	void Update(Float2 pos, Float2 target = Float2(0, 0));
	void Render();

	void SetColor(Float4 colour)
	{
		rect->SetColor(colour);
	}

};


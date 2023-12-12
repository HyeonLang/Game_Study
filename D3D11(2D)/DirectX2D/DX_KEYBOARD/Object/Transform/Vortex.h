#pragma once
class Vortex : public Transform
{
private:
	Circle* circle;
	float dir;
	// 원의 회전 방향과 속도

public:
	Vortex(Float2 p, Float2 s, float angle, float rad, int vx_count, float d, D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Vortex();

	void Update(Matrix* parent = NULL);
	void Render();

	void SetColor(Float4 colour)
	{
		circle->SetColor(colour);
	}
};

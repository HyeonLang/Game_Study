#include "pch.h"

Vortex::Vortex(Float2 p, Float2 s, float angle, float rad,int vx_count, 
	float d ,D3D11_PRIMITIVE_TOPOLOGY t)
	: Transform(p, s, angle), dir(d)
{
	circle = new Circle(p, rad, angle, t, vx_count);
}

Vortex::~Vortex()
{
	delete circle;
}

void Vortex::Update(Matrix* parent)
{
	angle += dir * 0.001f;
	// 생성자에서 입력한 회전 방향, 속도를 update시 회전각에 반영

	WorldTransform(parent);
	// 변경된 값을 오브젝트에 적용
}

void Vortex::Render()
{
	circle->Render();
}

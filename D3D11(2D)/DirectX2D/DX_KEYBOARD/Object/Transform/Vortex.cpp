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
	// �����ڿ��� �Է��� ȸ�� ����, �ӵ��� update�� ȸ������ �ݿ�

	WorldTransform(parent);
	// ����� ���� ������Ʈ�� ����
}

void Vortex::Render()
{
	circle->Render();
}

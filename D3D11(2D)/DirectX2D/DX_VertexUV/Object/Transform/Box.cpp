#include "pch.h"
#include "Box.h"

Box::Box(Float2 p, Float2 s, float a, D3D11_PRIMITIVE_TOPOLOGY t)
	: Transform(p, s, a)
{
	rect = new Rect(p, t);
}

Box::~Box()
{
	delete rect;
}

void Box::Update(Float2 pos, Float2 target)
{
	// ���� ������ �ۼ�
	  
	SetPos(pos);	// �Է¹��� ��ǥ�� �� ������Ʈ�� ���������� ���

	WorldUpdate();
	// ó�� �Ϸ� �� ���� ��ġ�� ������Ŀ� ������Ʈ
}

void Box::Render()
{
	rect->Render();
}

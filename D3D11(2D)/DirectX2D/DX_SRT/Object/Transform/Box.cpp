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

void Box::Update(Matrix* parent)
{
	// 수정 내용을 작성 

	WorldTransform(parent);
	// 처리 완료 후 최종 위치를 월드행렬에 업데이트
}

void Box::Render()
{
	rect->Render();
}

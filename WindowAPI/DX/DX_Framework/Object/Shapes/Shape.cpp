#include "framework.h"
#include "Shape.h"

Shape::Shape(float x, float y)
{
	pos_x = x;
	pos_y = y;
	VB = NULL;
	// 이 Shape 클래스는 상속용으로 만든 클래스, 실제 버퍼 이용은 상속받은 클래스에서 이용.
}

Shape::~Shape()
{
	VB->Release();	// VB의 NULL 체크는 상속받지 않고 사용하는걸 상정하지 않았으므로 하지않음.
}

#include "framework.h"
#include "Shape.h"

Shape::Shape(float x, float y)
{
	pos_x = x;
	pos_y = y;
	VB = NULL;
	// �� Shape Ŭ������ ��ӿ����� ���� Ŭ����, ���� ���� �̿��� ��ӹ��� Ŭ�������� �̿�.
}

Shape::~Shape()
{
	VB->Release();	// VB�� NULL üũ�� ��ӹ��� �ʰ� ����ϴ°� �������� �ʾ����Ƿ� ��������.
}

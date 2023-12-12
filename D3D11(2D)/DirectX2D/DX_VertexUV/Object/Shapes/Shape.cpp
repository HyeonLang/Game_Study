#include "pch.h"

Shape::Shape(float x, float y)
{
	pos_x = x;
	pos_y = y;
	VB = nullptr;
	// 이 Shape라는 클래스는
	// 실제 오브젝트를 관리하는데 사용할 클래스에 상속시켜서 사용할 클래스이므로
	// 이 클래스의 객체만 만든 상황에서는 버퍼를 만들 이유가 없음
	// 따라서 부모 클래스로서의 생성자만 이리 미리 만들어두는 것에 불과
}

Shape::~Shape()
{
}

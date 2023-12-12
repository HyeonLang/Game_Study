#include "pch.h"

Vector2::Vector2()
	: Float2(0, 0)
{
}

Vector2::Vector2(float x, float y)
	: Float2(x, y)
{
}

Vector2::Vector2(Float2 value)
	: Float2(value)
{
}

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


Vector2 Vector2::operator+ (const Vector2& value) const
{
	return Vector2(x + value.x, y + value.y);
}

Vector2 Vector2::operator- (const Vector2& value) const
{
	return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator* (const Vector2& value) const
{
	return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator/ (const Vector2& value) const
{
	return Vector2(x / value.x, y / value.y);
}

Vector2 Vector2::operator* (const float& value) const
{
	return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/ (const float& value) const
{
	return Vector2(x / value, y / value);
}

void Vector2::operator+= (const Vector2& value)
{
	x += value.x;
	y += value.y;
}

void Vector2::operator-= (const Vector2& value)
{
	x -= value.x;
	y -= value.y;
}

void Vector2::operator*= (const float& value) 
{
	x *= value;
	y *= value;
}

void Vector2::operator/= (const float& value) 
{
	x /= value;
	y /= value;
}

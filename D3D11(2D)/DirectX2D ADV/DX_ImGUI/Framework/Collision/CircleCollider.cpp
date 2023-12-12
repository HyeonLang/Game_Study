#include "pch.h"

CircleCollider::CircleCollider()
{
	type = TYPE::CIRCLE;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::IsPointCollision(Vector2 point)
{
	return false;
}

bool CircleCollider::IsCircleCollision(CircleCollider* collider)
{
	return false;
}

bool CircleCollider::IsRectCollision(RectCollider* collider)
{
	return false;
}

void CircleCollider::CreateLine()
{
}

#include "pch.h"

RectCollider::RectCollider(Vector2 size)
    : size(size)
{
    type = TYPE::RECT;
    
    CreateLine();
}

RectCollider::~RectCollider()
{
}

bool RectCollider::IsPointCollision(Vector2 point)
{
    Vector2 half = Size() * 0.5f;

    float left = GlobalPos().x - half.x;
    float right = GlobalPos().x + half.x;
    float top = GlobalPos().y - half.y;
    float bottom = GlobalPos().y + half.y;
    
    // 꼭지점이 내부에 있으면
    if (point.x > left && point.x < right)
        if (point.y > top && point.y < bottom)
            return true;
    return false;
}

bool RectCollider::IsCircleCollision(CircleCollider* collider)
{
    return false;
}

bool RectCollider::IsRectCollision(RectCollider* collider)
    // 사각형-사각형 : 어느 한 꼭지점이 상대 내부에 있으면 충돌
{
    Vector2 half = Size() * 0.5f;
    
    float left = GlobalPos().x - half.x;
    float right = GlobalPos().x + half.x;
    float top = GlobalPos().y - half.y;
    float bottom = GlobalPos().y + half.y;
    // 충돌 판정 범위

    half = collider->Size() * 0.5f;

    float desc_left = collider->GlobalPos().x - half.x;
    float desc_right = collider->GlobalPos().x + half.x;
    float desc_top = collider->GlobalPos().y - half.y;
    float desc_bottom = collider->GlobalPos().y + half.y;
    // 상대의 충돌 판정 범위

    if (collider->IsPointCollision(Vector2(left, top))
        || collider->IsPointCollision(Vector2(left, bottom))
        || collider->IsPointCollision(Vector2(right, top))
        || collider->IsPointCollision(Vector2(right, bottom))
        || IsPointCollision(Vector2(desc_left, desc_top))
        || IsPointCollision(Vector2(desc_left, desc_bottom))
        || IsPointCollision(Vector2(desc_right, desc_top))
        || IsPointCollision(Vector2(desc_right, desc_bottom)))
        return true;
    else
        return false;

}

void RectCollider::CreateLine() // 판정 박스 라인 그리기
{
    Vector2 half = size * 0.5f;

    verticies.emplace_back(-half.x, half.y);
    verticies.emplace_back(half.x, half.y);
    verticies.emplace_back(half.x, -half.y);
    verticies.emplace_back(-half.x, -half.y);
    verticies.emplace_back(-half.x, half.y);

    vertexBuffer = new VertexBuffer(verticies.data(), sizeof(VertexPos), verticies.size());
}

#include "stdafx.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(Context* const context, Actor* actor, TransformComponent* transform)
    : IComponent(context, actor, transform)
{
    D3DXMatrixIdentity(&local);
    D3DXMatrixIdentity(&world);
    UpdateTransform();
}

TransformComponent::~TransformComponent()
{
    Destroy();
}

void TransformComponent::Initialize()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::Destroy()
{
}

void TransformComponent::SetLocalScale(const D3DXVECTOR3& scale)
{
    if (this->local_scale == scale) return;

    this->local_scale = scale;
    UpdateTransform();
}

void TransformComponent::SetLocalPosition(const D3DXVECTOR3& position)
{
    if (this->local_position == position) return;

    this->local_position = position;
    UpdateTransform();
}

void TransformComponent::SetLocalRotation(const D3DXVECTOR3& rotation)
{
    if (this->local_rotation == rotation) return;

    this->local_rotation = rotation;
    UpdateTransform();
}

const D3DXVECTOR3 TransformComponent::GetScale()
{
    D3DXVECTOR3 world_scale;

    D3DXQUATERNION temp1;
    D3DXVECTOR3 temp2;
    // D3DXMatrixDecompose(s, r, t, martix) : 특정 martix를 s, r, t 값으로 분할
    D3DXMatrixDecompose(&world_scale, &temp1, &temp2, &world);

    // 과제 : 오일러각, 짐벌락 문제, 쿼터니언 조사

    return world_scale;
}

void TransformComponent::SetScale(const D3DXVECTOR3& world_scale)
{
    if (GetScale() == world_scale) return;

    if (HasParent() == true)
    {
        D3DXVECTOR3 scale;
        D3DXVECTOR3 parent_scale = parent.lock()->GetScale();
        scale.x = world_scale.x / parent_scale.x;
        scale.y = world_scale.y / parent_scale.y;
        scale.z = world_scale.z / parent_scale.z;

        SetLocalScale(scale);
    }
    else
        SetLocalScale(world_scale);

}

const D3DXVECTOR3 TransformComponent::GetPosition()
{
    D3DXVECTOR3 world_position;

    D3DXQUATERNION temp1;
    D3DXVECTOR3 temp2;
    D3DXMatrixDecompose(&temp2, &temp1, &world_position, &world);

    return world_position;
}

void TransformComponent::SetPosition(const D3DXVECTOR3& world_position)
{
    if (GetPosition() == world_position) return;

    if (HasParent() == true)
    {
        D3DXMATRIX inverse;
        D3DXMatrixInverse(&inverse, nullptr, &parent.lock()->GetWorldMatrix());

        D3DXVECTOR3 position;
        D3DXVec3TransformCoord(&position, &world_position, &inverse);

        SetLocalPosition(position);
    }
    else
        SetLocalPosition(world_position);
}

const D3DXVECTOR3 TransformComponent::GetRotation()
{
    D3DXVECTOR3 temp1;

    D3DXQUATERNION world_rotation;
    D3DXVECTOR3 temp2;
    D3DXMatrixDecompose(&temp2, &world_rotation, &temp1, &world);

    D3DXMATRIX rotation;
    D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

    return D3DXVECTOR3 // Y - X - Z
    (
        atan2(rotation._31, rotation._33),
        atan2(-rotation._32, sqrt(pow(rotation._12, 2) + pow(rotation._22, 2))),
        atan2(rotation._12, rotation._22)
    );
}

void TransformComponent::SetRotation(const D3DXVECTOR3& world_rotation)
{
    if (GetRotation() == world_rotation) return;

    if (HasParent() == true)
    {
        D3DXMATRIX inverse;
        auto my_world_rotation = GetWorldRotationMatrix();
        D3DXMatrixInverse(&inverse, nullptr, &my_world_rotation);

        D3DXVECTOR3 rotation;
        D3DXVec3TransformNormal(&rotation, &world_rotation, &inverse);

        SetLocalRotation(rotation);
    }
    else
        SetLocalRotation(world_rotation);
}

const D3DXMATRIX TransformComponent::GetWorldRotationMatrix()
{
    D3DXQUATERNION world_rotation;
    D3DXVECTOR3 temp;

    D3DXMatrixDecompose(&temp, &world_rotation, &temp, &world);

    D3DXMATRIX rotation;
    D3DXMatrixRotationQuaternion(&rotation, &world_rotation);

    return rotation;
}

const D3DXVECTOR3 TransformComponent::GetRight() const
{
    D3DXVECTOR3 right;
    D3DXVECTOR3 vec(1, 0, 0);

    D3DXVec3TransformNormal(&right, &vec, &world);

    return right;
}

const D3DXVECTOR3 TransformComponent::GetUp() const
{
    D3DXVECTOR3 up;
    D3DXVECTOR3 vec(0, 1, 0);

    D3DXVec3TransformNormal(&up, &vec, &world);

    return up;
}

const D3DXVECTOR3 TransformComponent::GetForward() const
{
    D3DXVECTOR3 forward;
    D3DXVECTOR3 vec(0, 0, 1);

    D3DXVec3TransformNormal(&forward, &vec, &world);

    return forward;
}

void TransformComponent::UpdateTransform()
{
    D3DXMATRIX S, R, T;
    D3DXMatrixScaling(&S, local_scale.x, local_scale.y, local_scale.z);
    D3DXMatrixRotationYawPitchRoll(&R, local_rotation.y, local_rotation.x, local_rotation.z);
    D3DXMatrixTranslation(&T, local_position.x, local_position.y, local_position.z);

    local = S * R * T;

    if (HasParent() == true)
        world = local * parent.lock()->GetWorldMatrix();
    else
        world = local;

    for (const auto& child : childs)
        if (child.expired() != true)
            child.lock()->UpdateTransform();
}

void TransformComponent::SetParent(std::shared_ptr<TransformComponent> const new_parent)
{
    if (new_parent.get() == this) return;

    parent = new_parent;
}

bool TransformComponent::HasChilds() const
{

    for (const auto& child : childs)
        if (child.expired() != true) return true;

    return false;
}

uint TransformComponent::GetChildCount() const
{
    int count = 0;
    for (const auto& child : childs)
        if (child.expired() != true) count++;

    return count;
}

void TransformComponent::AddChild(std::shared_ptr<TransformComponent> const child)
{
    if (child.get() == this) return;

    childs.emplace_back(child);
}

#include "stdafx.h"
#include "Actor.h"
#include"Component/TransformComponent.h"
#include"Component/MeshRendererComponent.h"

Actor::Actor(Context* const context)
	:context(context)
{
	AddComponent<TransformComponent>();
}

Actor::~Actor()
{
	components.clear();
	components.shrink_to_fit();
}

void Actor::Update()
{
	if (is_active == false) return;

	for (const auto& component : components)
	{
		if (component->IsEnabled() != true)
			continue;

		component->Update();
	}
}

void Actor::Destroy()
{
	for (const auto& component : components)
		component->Destroy();
}

bool Actor::HasComponent(const ComponentType& type)
{
	for (const auto& component : components)
		if (component->GetComponentType() == type)
			return true;

	return false;
}

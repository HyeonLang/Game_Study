#pragma once
#include "IComponent.h"
class MoveScriptComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~MoveScriptComponent() = default;

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Destroy() override;
};


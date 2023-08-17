#pragma once
#include "IComponent.h"
class MoveScriptComponent final : public IComponent
{
public:
	MoveScriptComponent(
		class Actor* const actor,
		class TransformComponent* const transform
	);
	~MoveScriptComponent() = default;

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Destroy() override;
};


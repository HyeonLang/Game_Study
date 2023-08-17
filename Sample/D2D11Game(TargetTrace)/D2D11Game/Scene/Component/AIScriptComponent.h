#pragma once
#include "IComponent.h"

class AIScriptComponent final : public IComponent
{
public:
	AIScriptComponent(
		class Actor* const actor,
		class TransformComponent* const transform
	);
	~AIScriptComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

private:
	enum class Direction
	{
		Up,		// 0
		Right,	// 1 
		Down,	// 2
		Left	// 3
	};

private:
	Stopwatch stopwatch;
	Direction direction = Direction::Right;
};


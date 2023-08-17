#pragma once
#include "IComponent.h"

enum Trace_State
{
	Trace,
	Stop,
	Avoid
};

class TargetTraceComponent : public IComponent
{
public:
	using IComponent::IComponent;
	~TargetTraceComponent() = default;

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Destroy() override;

	void SetTarget(std::weak_ptr<class Actor> target) { this->target = target; }

private:
	std::weak_ptr<class Actor> target;
	Stopwatch timer;

	float speed = 1000;
	Trace_State cur_trace_state = Trace;
};


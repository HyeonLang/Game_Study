#pragma once
#include"IComponent.h"

class CameraComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~CameraComponent() = default;

	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Destroy() override;

	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjectionMatrix() const { return projection; }

private:
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

};


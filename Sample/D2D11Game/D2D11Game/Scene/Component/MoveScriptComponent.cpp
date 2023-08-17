#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"
#include "MeshRendererComponent.h"
#include "../Actor.h"

void MoveScriptComponent::Update()
{
	D3DXVECTOR3 position = transform->GetPosition();

	auto input_manager = context->GetSubsystem<InputManager>();

	if (input_manager->IsKeyDown(DIK_W) || input_manager->IsKeyHold(DIK_W)) position.y++;
	if (input_manager->GetKeyState(DIK_S, KEY_DOWN | KEY_HOLD)) position.y--;
	if (GetAsyncKeyState('D') & 0x8000) position.x++;
	if (GetAsyncKeyState('A') & 0x8000) position.x--;
	
	transform->SetPosition(position);

	//IMGUI

	if (ImGui::Begin("Transform"))
	{
		auto position = transform->GetPosition();

		ImGui::InputFloat3("Position", position);

		transform->SetPosition(position);
	}
	ImGui::End();

	if (ImGui::Begin("Transform"))
	{
		auto scale = transform->GetScale();

		ImGui::SliderFloat3("Scale", scale, 0.0f, 300.0f);

		transform->SetScale(scale);
	}
	ImGui::End();

	if (ImGui::Begin("Actor"))
	{
		auto renderer = actor->GetComponent<MeshRendererComponent>();
		auto mesh_is_enable = renderer->IsEnabled();

		ImGui::Checkbox("Render", &mesh_is_enable);

		renderer->SetEnabled(mesh_is_enable);
	}
	ImGui::End();
}

void MoveScriptComponent::Initialize()
{
}

void MoveScriptComponent::Destroy()
{
}

// Renderer_passes.cpp
#include"stdafx.h"
#include"Renderer.h"
#include"Scene/Actor.h"
#include"Scene/Scene.h"
#include"Scene/Component/CameraComponent.h"
#include"Scene/Component/MeshRendererComponent.h"
#include"Scene/Component/TransformComponent.h"
#include"Scene/Component/AnimatorComponent.h"

void Renderer::PassMain()
{
	std::vector<Actor*> actors = renderables[RenderableType::Opaque];

	if (actors.empty())
		return;

	for (const auto& actor : actors)
	{
		if(actor->IsActive() != true)
			continue;

		auto renderable = actor->GetComponent<MeshRendererComponent>();
		if (renderable == nullptr || renderable->IsEnabled() != true)
			continue;

		auto transform = actor->GetComponent<TransformComponent>();
		if (transform == nullptr)
			continue;

		D3D11_PipelineState pipeline_state;
		pipeline_state.input_layout = renderable->GetInputLayout().get();
		pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		pipeline_state.vertex_shader = renderable->GetVertexShader().get();
		pipeline_state.pixel_shader = renderable->GetPixelShader().get();
		pipeline_state.rasterizer_state = rasterizers[RasterizerStateType::Cull_Back_FILL_Solid].get();
		pipeline_state.blend_state = blend_states[BlendStateType::Alpha].get();

		if (pipeline->Begin(pipeline_state))
		{
			pipeline->SetVertexBuffer(renderable->GetVertexBuffer().get());
			pipeline->SetIndexBuffer(renderable->GetIndexBuffer().get());

			D3DXMatrixTranspose(&cpu_object_buffer.world, &transform->GetWorldMatrix());
			UpdateObjectBuffer();

			pipeline->SetConstantBuffer(1, ShaderScope_VS, gpu_object_buffer.get());

			if (auto animator = actor->GetComponent<AnimatorComponent>())
			{
				auto current_keyframe = animator->GetCurrentKeyframe();
				cpu_animation_buffer.sprite_offset = current_keyframe->offset;
				cpu_animation_buffer.sprite_size = current_keyframe->size;
				cpu_animation_buffer.texture_size = animator->GetCurrentAnimation()->GetSpriteTextureSize();
				cpu_animation_buffer.is_animated = 1.0f;
				UpdateAnimationBuffer();

				pipeline->SetConstantBuffer(2, ShaderScope_VS | ShaderScope_PS, gpu_animation_buffer.get());
				pipeline->SetShaderResource(0, ShaderScope_PS, animator->GetCurrentAnimation()->GetSpriteTexture().get());
			}
			else
			{
				cpu_animation_buffer.sprite_offset = D3DXVECTOR2(0, 0);
				cpu_animation_buffer.sprite_size = D3DXVECTOR2(1, 1);
				cpu_animation_buffer.texture_size = D3DXVECTOR2(1, 1);
				cpu_animation_buffer.is_animated = 0.0f;
				UpdateAnimationBuffer();

				pipeline->SetConstantBuffer(2, ShaderScope_VS | ShaderScope_PS, gpu_animation_buffer.get());
				pipeline->SetShaderResource_nullptr(0, ShaderScope_PS);
			}

			pipeline->DrawIndexed
			(
				renderable->GetIndexBuffer()->GetCount(),
				renderable->GetIndexBuffer()->GetOffset(),
				renderable->GetVertexBuffer()->GetOffset()
			);
			pipeline->End();
		}
	}

	bool a = true;
	ImGui::ShowDemoWindow(&a);

	// Rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


#pragma once
#include "IComponent.h"

enum class MeshType : uint
{
	Quad,
};

class MeshRendererComponent final : public IComponent
{
public:
	using IComponent::IComponent;
	~MeshRendererComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Destroy() override;

	//==================================
	// [Mesh]
	//==================================
	std::shared_ptr<D3D11_VertexBuffer> GetVertexBuffer() const { return vertex_buffer; }
	std::shared_ptr<D3D11_IndexBuffer> GetIndexBuffer() const { return index_buffer; }
	void SetStandardMesh();

	//==================================
	// [Material]
	//==================================
	std::shared_ptr<D3D11_Shader> GetVertexShader() const { return vertex_shader; }
	std::shared_ptr<D3D11_Shader> GetPixelShader() const { return pixel_shader; }
	std::shared_ptr<D3D11_InputLayout> GetInputLayout() const { return input_layout; }
	void SetStandardMaterial();

private:
	MeshType mesh_type = MeshType::Quad;

	std::shared_ptr<D3D11_VertexBuffer> vertex_buffer = nullptr;
	std::shared_ptr<D3D11_IndexBuffer> index_buffer = nullptr;
	std::shared_ptr<D3D11_InputLayout> input_layout = nullptr;
	std::shared_ptr<D3D11_Shader> vertex_shader = nullptr;
	std::shared_ptr<D3D11_Shader> pixel_shader = nullptr;
};


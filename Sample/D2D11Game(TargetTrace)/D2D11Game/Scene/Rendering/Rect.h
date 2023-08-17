#pragma once

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

struct COLOR_DATA
{
	D3DXCOLOR color;
};

enum class Direction
{
	Up,		// 0
	Right,	// 1 
	Down,	// 2
	Left	// 3
};

class Rect
{
public:
	Rect(class Graphics* graphics, const D3DXCOLOR& color);
	virtual ~Rect();

	void SetPosition(const D3DXVECTOR3& position) { this->position = position; }
	void SetScale(const D3DXVECTOR3& scale) { this->scale = scale; }

	const bool& IsActive() const { return is_active; }

	const D3DXVECTOR3& GetPosition() { return position; }
	const D3DXVECTOR3& GetScale() { return scale; }

	void Update();
	void Render(D3D11_Pipeline* pipeline);

protected:
	virtual void Move() = 0;
	virtual void Restore() = 0;
	virtual void Event() = 0;

protected:
	D3D11_VertexBuffer* vertex_buffer = nullptr;
	D3D11_IndexBuffer* index_buffer = nullptr;
	D3D11_InputLayout* input_layout = nullptr;
	D3D11_Shader* vertex_shader = nullptr;
	D3D11_Shader* pixel_shader = nullptr;
	D3D11_ConstantBuffer* gpu_buffer = nullptr;
	D3D11_RasterizerState* rasterizer_state = nullptr;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 scale = D3DXVECTOR3(100, 100, 1);

	D3DXMATRIX world;

	D3D11_ConstantBuffer* color_buffer = nullptr;
	D3DXCOLOR intersect_color = D3DXCOLOR(1, 1, 1, 1);

	bool is_active = true;
	bool is_intersect = false;
};


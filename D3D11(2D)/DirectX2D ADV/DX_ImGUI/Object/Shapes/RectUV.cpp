#include "pch.h"

RectUV::RectUV(Float2 pos, Float2 size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(pos.x, pos.y), type(t)
{
	float left = -size.x * 0.5f;
	float right = size.x * 0.5f;
	float top = -size.y * 0.5f;
	float bottom = size.y * 0.5f;

	switch (type)
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:

		verticies_uv.emplace_back(left, top, 0, 0);
		// 0, 0은 사진의 왼쪽 위를 기준으로 했을 때의 사진에서의 위치
		// <이 정점은 사진에서의 해당 위치를 가리킨다> 라고 지정한다.
		verticies_uv.emplace_back(right, top, 1, 0);
		verticies_uv.emplace_back(left, bottom, 0, 1);

		verticies_uv.emplace_back(left, bottom, 0, 1);
		verticies_uv.emplace_back(right, top, 1, 0);
		verticies_uv.emplace_back(right, bottom, 1, 1);
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:

		verticies_uv.emplace_back(left, top, 0, 0);
		verticies_uv.emplace_back(right, top, 1, 0);
		verticies_uv.emplace_back(left, bottom, 0, 1);
		verticies_uv.emplace_back(right, bottom, 1, 1);
		break;

	default:
		break;
	}

	

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexUV.hlsl", flags, 1);
	PS = new PixelShader(L"Shader/PixelShader/PixelUV.hlsl", flags);

	VB = new VertexBuffer(verticies_uv.data(), sizeof(VertexUV), verticies_uv.size());

	CB = new ColourBuffer();

}

RectUV::~RectUV()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;

}

void RectUV::Render()
{
	CB->SetPS(0);
	VB->Set(type);

	VS->Set();
	PS->Set();

	DVC->Draw(verticies_uv.size(), 0);
}

void RectUV::Render(ID3D11ShaderResourceView** srv, ID3D11SamplerState** sampler_state)
{
}

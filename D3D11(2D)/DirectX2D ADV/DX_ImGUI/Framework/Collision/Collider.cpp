#include "pch.h"

Collider::Collider()
{
	this->SetActive(true);

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	vertexShader = new VertexShader(L"Shader/VertexShader/VertexPos.hlsl", flags, 1);
	pixelShader = new PixelShader(L"Shader/PixelShader/PixelPos.hlsl", flags);

	colourBuffer = new ColourBuffer();
	colourBuffer->data.colour = { 0, 1, 0, 1 };

	worldBuffer = new MatrixBuffer();
}

Collider::~Collider()
{
	delete vertexShader;
	delete pixelShader;


	delete colourBuffer;

	delete worldBuffer;
}

void Collider::Render()
{
	if (!is_active) return;

	worldBuffer->Set(world);
	worldBuffer->SetVS(0);
	colourBuffer->SetPS(0);

	vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	vertexShader->Set();
	pixelShader->Set();

	DVC->Draw(verticies.size(), 0);
}

bool Collider::IsCollision(Collider* collider)	// 다른 오브젝트의 충돌범위를 받아 충돌여부 매시간 체크
{
	if (!is_active) return false;

	switch (collider->type)
	{
	case TYPE::RECT :
		return IsRectCollision((RectCollider*)collider);
		break;
	case TYPE::CIRCLE :
		return IsCircleCollision((CircleCollider*)collider);
		break;
	default:
		break;
	}
}

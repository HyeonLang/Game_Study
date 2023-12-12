#include "pch.h"
#include "Circle.h"

Circle::Circle(Float2 pos, float size, float a, D3D11_PRIMITIVE_TOPOLOGY t, int vx_count)
	: Shape(pos.x, pos.y), type(t), angle(a)
{
	// �츮�� ������ ���ؼ� ȭ�鿡 �׸� �� ����ϴ� ��ǥ�� ȭ�� �� ������ �������� ����Ѵٰ� ����
	// ��Ȯ���� ����Ʈ�� ���� �����ǥ�� �̿��ؼ� �����ϴ� ���
	// �� ����Ʈ�� ���� ������ ������ WVP ��ȯ�� ���� ������ �� ���� ������ ����

	radius = size;
	angle += 2 * M_PI;


	
	switch (type)
	{
	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= vx_count; i++) {
			// TRIANGLESTRIP�� ����ϰ� ������ �Էµƴ� ������ �̿��� ���� �׸��� ����
			// �������� �ﰢ�� ������ �ƴ�, �� �ϳ� ������ �׸��� ���

			verticies.emplace_back(cos(angle) * radius, sin(angle) * radius, 1.0f, 1.0f, 1.0f);
			angle -= 2 * M_PI / float(vx_count);
		}
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i <= vx_count; i++) {
			verticies.emplace_back(-cos(angle) * radius, -sin(angle) * radius, 1.0f, 1.0f, 1.0f);
			verticies.emplace_back(0, 0, 1.0f, 1.0f, 1.0f);
			// �߾��� ����ϴ� �� �κ�
			// �߾��� ������ ����ó�� ��ǥ�� ������ �� �ƴѾƿ� 0, 0���� ����

			// �������� �� Transform�� ��ġ�� ����ؼ� ������ �׸��� ������
			// Ʈ�������� ��ġ ��ü�� �� ������ �׷����� ��ġ
			// -> �� �׸��� �׷����� ��ġ ��ü�� ��ü ��ġ���� Ư���� �ʿ䰡 ����
			// �� ������ Transform���� ��� �������� ������ �������ִ����� �������ָ� �ȴ�.
			angle -= 2 * M_PI / float(vx_count);
			verticies.emplace_back(-cos(angle) * radius, -sin(angle) * radius, 1.0f, 1.0f, 1.0f);
		}
		break;

	default:
		break;

	}
	

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(verticies.data(), sizeof(Vertex), verticies.size());
	CB = new ColourBuffer();
}

Circle::~Circle()
{
	VS->Release();
	PS->Release();
	delete VB;
	delete CB;
}

void Circle::Render()
{
	if (CB->data.colour.x != 0.0f || CB->data.colour.y != 0.0f || CB->data.colour.z != 0.0f)
		CB->SetPS(0);
	// �� ���� ���� ���� ������ �̸� �ݿ�
	// �ȼ����̴��� �⺻ ���� ������
	// �� ���۰� �������� �ƴ� �ٸ� ���̸� 0�� ���Կ� �ѱ��

	VB->Set(type);
	VS->Set();
	PS->Set();

	DVC->Draw(verticies.size(), 0);
}

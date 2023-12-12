#include "pch.h"
#include "Rect.h"


Rect::Rect(Float2 pos, D3D11_PRIMITIVE_TOPOLOGY t)
	:Shape(pos.x, pos.y), type(t)
	// x, y���� pos�� �̿��ϴ� ���� : Transform�� �⺻�̹Ƿ� ���� �ɰ��� �Է����� �ʰ� pos : Float2 ��ü�� �Է�
{
    switch (type)   // �Ű����� ���� �ʱ�ȭ�� ��� ������ ����ϴ� ���� �����ϴ�.
    {
    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
        verticies.emplace_back(+ 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back(- 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back(- 50, - 50, 1.0f, 1.0f, 1.0f);
        // 1.0f ������ �ƴ� ���� ��ǥ�� �״�� �Է��ϴ� ��.
        // API���� ���� �������� ���� 
        verticies.emplace_back( - 50, - 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back( + 50, - 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back( + 50, + 50, 1.0f, 1.0f, 1.0f);
        break;

    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:

        verticies.emplace_back(+ 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back(- 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back( - 50, - 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back( + 50, - 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back( + 50, + 50, 1.0f, 1.0f, 1.0f);
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

Rect::~Rect()
{
    VS->Release();
    PS->Release();
    delete VB;
    delete CB;
}

void Rect::Render()
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

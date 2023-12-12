#include "pch.h"
#include "Rect.h"


Rect::Rect(Float2 pos, D3D11_PRIMITIVE_TOPOLOGY t)
	:Shape(pos.x, pos.y), type(t)
	// x, y없이 pos만 이용하는 이유 : Transform이 기본이므로 값을 쪼개서 입력하지 않고 pos : Float2 자체를 입력
{
    switch (type)   // 매개변수 보다 초기화된 멤버 변수를 사용하는 것이 안전하다.
    {
    case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
        verticies.emplace_back(+ 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back(- 50, + 50, 1.0f, 1.0f, 1.0f);
        verticies.emplace_back(- 50, - 50, 1.0f, 1.0f, 1.0f);
        // 1.0f 범위가 아닌 절대 좌표를 그대로 입력하는 중.
        // API때와 같이 왼쪽위가 기준 
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
    // 색 버퍼 값이 따로 있으면 이를 반영
    // 픽셀셰이더의 기본 색은 검은색
    // 색 버퍼가 검은색이 아닌 다른 색이면 0번 슬롯에 넘기기

    VB->Set(type);
    VS->Set();
    PS->Set();

    DVC->Draw(verticies.size(), 0);
}

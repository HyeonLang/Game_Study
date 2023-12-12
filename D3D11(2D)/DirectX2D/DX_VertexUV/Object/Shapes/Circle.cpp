#include "pch.h"
#include "Circle.h"

Circle::Circle(Float2 pos, float size, float a, D3D11_PRIMITIVE_TOPOLOGY t, int vx_count)
	: Shape(pos.x, pos.y), type(t), angle(a)
{
	// 우리가 정점을 통해서 화면에 그릴 때 사용하는 좌표는 화면 내 비율을 기준으로 계산한다고 설명
	// 정확히는 뷰포트를 통한 상대좌표를 이용해서 결정하는 방식
	// 이 뷰포트에 대한 개념은 다음주 WVP 변환에 대해 설명할 때 같이 설명할 예정

	radius = size;
	angle += 2 * M_PI;


	
	switch (type)
	{
	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= vx_count; i++) {
			// TRIANGLESTRIP과 비슷하게 기존에 입력됐던 정점을 이용해 새로 그리는 형식
			// 차이점은 삼각형 단위가 아닌, 선 하나 단위로 그리는 방식

			verticies.emplace_back(cos(angle) * radius, sin(angle) * radius, 1.0f, 1.0f, 1.0f);
			angle -= 2 * M_PI / float(vx_count);
		}
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i <= vx_count; i++) {
			verticies.emplace_back(-cos(angle) * radius, -sin(angle) * radius, 1.0f, 1.0f, 1.0f);
			verticies.emplace_back(0, 0, 1.0f, 1.0f, 1.0f);
			// 중앙을 담당하는 점 부분
			// 중앙의 값으로 기존처럼 좌표를 지정한 게 아닌아예 0, 0으로 지정

			// 도형들은 각 Transform의 위치에 기반해서 도형을 그리기 때문에
			// 트랜스폼의 위치 자체가 이 도형이 그려지는 위치
			// -> 이 그림이 그려지는 위치 자체를 전체 위치에서 특정할 필요가 없고
			// 각 정점이 Transform에서 어느 방향으로 어디까지 떨어져있는지만 지정해주면 된다.
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
	// 색 버퍼 값이 따로 있으면 이를 반영
	// 픽셀셰이더의 기본 색은 검은색
	// 색 버퍼가 검은색이 아닌 다른 색이면 0번 슬롯에 넘기기

	VB->Set(type);
	VS->Set();
	PS->Set();

	DVC->Draw(verticies.size(), 0);
}

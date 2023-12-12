#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;	// 셰이더를 생성하기 위해 필요한 플래그를 미리 설정
	
	// 정점 셰이더와 픽셀 셰이더를 셰이더 주소가 있는 파일에 생성
	VS = new VertexShader(L"../Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"../Shader/VertexShader.hlsl", flags);

	// 도형을 그리는 데 사용할 정점 생성
	vector<Vertex> vx_triangle_list =
	{
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f)
	};

	//
	
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
}

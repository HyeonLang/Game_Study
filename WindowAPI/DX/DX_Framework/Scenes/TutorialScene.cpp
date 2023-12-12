#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;	// ���̴��� �����ϱ� ���� �ʿ��� �÷��׸� �̸� ����
	
	// ���� ���̴��� �ȼ� ���̴��� ���̴� �ּҰ� �ִ� ���Ͽ� ����
	VS = new VertexShader(L"../Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"../Shader/VertexShader.hlsl", flags);

	// ������ �׸��� �� ����� ���� ����
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

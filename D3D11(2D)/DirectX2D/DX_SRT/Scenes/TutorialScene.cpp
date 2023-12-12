#include "pch.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	// ���̴� ������ �ʿ��� �÷��׸� �̸� ����

	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);
	// ���� ���̴��� �ȼ� ���̴��� ���̴� �ּҰ� �ִ� ���Ͽ� ����

	// ���� ������ �׸��� �� ����� ���� ����
	vector<Vertex> vx_triangle_list =
	{
		Vertex(-0.1f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.1f, 0.8f, 0.8f, 0.17f),
		Vertex(-0.8f, +0.8f, 0.8f, 0.8f, 0.17f),
	};

	list_triangle = new Triangle(vx_triangle_list,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vector<Vertex> vx_rect_list =
	{
		Vertex(-0.8f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.8f, -0.8f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.8f, -0.8f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.1f, 0.8f, 0.1f, 0.6f),
		Vertex(-0.1f, -0.8f, 0.8f, 0.1f, 0.6f),
	};

	list_rect = new Triangle(vx_rect_list,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	list_hexagon[0] = new Hexagon(960, 540,
		0.3f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	list_hexagon[1] = new Hexagon(560, 540,
		0.3f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	line_hexagon = new Hexagon(960, 180,
		0.4f, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	// �̷��� �� ���� ������ �׸��� Ŭ������ ����
	// �� ������ ���� ��带 �����صΰ� �ʿ��� ������ ��� ���� �����ε�
	// �츮�� ���ϴ� ������ ������ ���� �Է����� �ʿ� ����
	// ��ǥ�� ũ�⸸ �Է��ϴ� ������
	// �˾Ƽ� �� ������ �������� ������ �ϼ��� �������� ����ϵ��� ���� �� �ִ�

	// �̷� ������ ������Ʈ�� ����� ����
	// ������ �츮�� ���� ���α׷����� �⺻���� ���� ���

	// 
}

TutorialScene::~TutorialScene()
{
	delete(list_triangle);
	delete list_rect;
	for (int i = 0; i < 10; i++)
	{
		if(list_hexagon[i] != NULL)
			delete list_hexagon[i];
	}
	delete line_hexagon;
	VS->Release();
	PS->Release();
}

void TutorialScene::Update()
// ���� ���α׷��� �� �������� ���� ���� ��Ȳ�� ������Ʈ�ϴ� �Լ�
// �ð� ��� � ���� ���� ������ ���ؾ� �Ѵٸ� �� �Լ��� ���� ���������� ����

// ...������ ������ �� �Լ��� ����� ���� ������ �� �Լ��� ����
{


}

void TutorialScene::Render()
// ���� ����� ����ϴ� �κ�
// �� ���� ������� ��, ���� ������ ���ư� ������ �� �Լ��� ���� ȭ�鿡 ���
{
	Device::Get()->Clear();
	// ȭ���� �ʱ�ȭ��Ű�� �Լ��� Device���� �ҷ� ���

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	

	Device::Get()->GetDeviceContext()->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	Device::Get()->GetDeviceContext()->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// ����̽��� ���� ���̴��� �ȼ� ���̴��� ����

	Device::Get()->GetDeviceContext()->IASetInputLayout(VS->GetInputLayout());
	// VS ������ input_layout�� ������ device_context�� ����

	// ��������� �׸��� ���� Scene�� �׸� ȯ���� �����ϴ� �κ�
	// ������ʹ� ���������� ������ �׸��� �κ�

	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, list_triangle->GetBuffer(), &stride, &offset);
	// �ﰢ���� �����ϰ� �ִ� ������ ����� ���۸� ����̽��� ����
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_triangle->GetType());
	// �ﰢ���� �����ϰ� �ִ� ������ �׸� ����� ����̽��� ����

	Device::Get()->GetDeviceContext()->Draw(list_triangle->GetVertexSize(), 0);
	// ������ �� �������� �ﰢ���� �����ϰ� �ִ� ������ ������ŭ ������ �׸���� ��û
	
	// �ٸ� ������ �׸��� �ʹٸ� �� 3���� �ڵ带 ���� �̸��� �ٲ㼭 ���� 
	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, list_rect->GetBuffer(), &stride, &offset);
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_rect->GetType());

	Device::Get()->GetDeviceContext()->Draw(list_rect->GetVertexSize(), 0);



	for (int i = 0; i < 10; i++)
	{
		if (list_hexagon[i] == NULL)
			break;
		Device::Get()->GetDeviceContext()->IASetVertexBuffers
		(0, 1, list_hexagon[i]->GetBuffer(), &stride, &offset);
		Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_hexagon[i]->GetType());

		Device::Get()->GetDeviceContext()->Draw(list_hexagon[i]->GetVertexSize(), 0);
	}
	Device::Get()->GetDeviceContext()->IASetVertexBuffers
	(0, 1, line_hexagon->GetBuffer(), &stride, &offset);
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(line_hexagon->GetType());

	Device::Get()->GetDeviceContext()->Draw(line_hexagon->GetVertexSize(), 0);

	// ��������� Scene���� ������ �׸� �κ�

/*
���� :

������ ����ϴ� Ŭ������ �ϳ� �� ����
���� Scene���ٰ� �׷��� ��
Hexagon Ŭ������ ������� �Ͱ� ���� ������� Ŭ������ ���� ��

������ �׷ȴ� �������� ���� �����ص� ����

���� 1 : �׸� ������ ���������� �����ֿ� ���������� �ҹ�
���� 2 : ������ Ŭ�����μ� ���� ��
���� 3 : ������ "ó�� ���� ������ ��� ���� ȸ���� ���·� ���� ��"
�׸��� �� ȸ���� ���� Ŭ������ ��ü������ �޶�� ��
<- ������ ���� �ش� Ŭ������ ��ü�� �ּ� 3�� �̻� �����
������ ���� ȸ���� ������ �޶�� �Ѵ�



*/
}

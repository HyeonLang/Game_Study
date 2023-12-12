#include "pch.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;	// ���̴��� �����ϱ� ���� �ʿ��� �÷��׸� �̸� ����
	
	// ���� ���̴��� �ȼ� ���̴��� ���̴� �ּҰ� �ִ� ���Ͽ� ����
	VS = new VertexShader(L"Shader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/VertexShader.hlsl", flags);

	// ������ �׸��� �� ����� ���� ����
	vector<Vertex> vx_triangle_list =
	{
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.1f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.8f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.8f, 0.4f, 0.4f, 1.0f),
		Vertex(-0.1f, +0.1f, 0.4f, 0.4f, 1.0f)

	};

	// ���ǵ� ������ ���� ������ ����
	list_rect = new Triangles(vx_triangle_list, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
		������ �����ϴ� Ŭ������ ����� (Shape�� ��ӽ�Ű�� ����)
		�̰� TutorialScene�� ��ü�� �߰��Ͽ� ����غ���

		������ ��������� ��üó�� ���� 
		Render() ���ο��� ����ϵ��� ������

		�߰���ǥ : �� �ٸ�ü ����, �� ����
	*/
	// ������ ���� ���� ����Ʈ : �ﰢ�� 6�� ���� ����Ʈ
	vector<Vertex> vx_hexagon_list =
	{
		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
		// ���� ������ �ݵ�� �ð�������� ����

		// ���� ���� �� : ������ �߽� ��ǥ�� �߽��� �������� �Ѵ�.

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),

		Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),
		Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
		
	};

	// �߽ɰ� �������� ���� ������ ����
	hexagon = new Hexagons(calc_ratio_pos_x(960, 0), calc_ratio_pos_x(540, 0), 0.2f, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
		1. ������ �߽����� ũ�⸸ �����ϸ� �������� �����Ǵ� ���� Ŭ���� ����ϱ�
			: ��, ������
		
		1.5. TRIANGEL_STRIP�� �̿��Ͽ� 1���� �� ����
			: STRIP = �������� �̾ ��� �ﰢ���� ����
		
		2. ���� ������ ���� ������ ���� Pixel Shader ���� �ǽ� ����
	*/

	/*
		���� : TRIANGEL_STRIP�� ���� ������ �׸���

		STRIP : �̹� ����ߴ� ������ ���̿��ؼ�, ������ �׸��µ� �ʿ��� ������ ������ �� ���� ���� �׸��� ���
		�ٸ� ������ ����ϴ� ����� �簢�� ���� ������ ����

		�Ʒ��� �簢���� �ִ� �������� ��, �� ������ ��ȣ�� ���� ��
		1 2
		3 4

		TRIANGLE_LINE �������δ�
		(1 2 4) (4 3 1)
		(1 2 3) (2 4 3)
		������ �Է��ؼ� �̿�������

		STRIP �������δ�
		(1 2 3 4)�θ� �Է��ص� ����� ��
		(1 2 4 3)���� �Է��ϸ� �Ƹ� �� �� ��

		� ������ �̷����淡 �̷��� �Է��ص� ����� �Ǵ��� �����ϸ鼭,
		�� STRIP�� �̿��� ���� �׷��ͺ� ��

		�߰�)���� ���, ���� �������� ������� ��Ŀ��� 6�� �ƴ϶�
		���� �׸��� ����� ��ŭ ������ ������ �ϸ� ���� �׸� �� ����
		���� ��Ƶ� 20~30 ����?

		�߰�2)���� 27�� ���Ǳ����� �������δ� �Ұ���.
		�߼��Ⱓ �� �߰� ������ ������ �ڷḦ �����ϸ� ����������, �������� �̸� ������ ���� �䱸������ ���� ���̹Ƿ�
		������ ������ �ð��� �� ���´ٸ� �� �� �õ��غ� ���� ����
	*/
	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP �� �̿��� �ﰢ�� �����
	// 
	// �� ������ ��ȣ�� �ű�� ���� ǥ�� ����
	// ���� ��ȣ   x    y
	//    1      -0.8 -0.1
	//    2      -0.1 -0.1
	//    3      -0.8 -0.8
	//    4      -0.1 -0.8
	vector<Vertex> vx_strip_rect_list =
	{
		Vertex(-0.8f, -0.1f, 1.0f, 1.0f, 1.0f),
		Vertex(-0.1f, -0.1f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.8f, -0.8f, 1.0f, 0.0f, 0.0f),
		Vertex(-0.1f, -0.8f, 1.0f, 1.0f, 0.0f),
		Vertex(-0.8f, -0.9f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.0f, -0.85f, 0.4f, 0.4f, 1.0f)
		
	};
	strip_rect = new Triangles(vx_strip_rect_list, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// TRIANGLESTRIP�� ������ ���� �����Ѵ�
	// ù(Ȧ��)��° �ﰢ�� : k, k+1, k+2��° ������ �̿��ؼ� �ﰢ���� �׸� 
	// �ι�(¦��)��° �ﰢ�� : k+2, k+1, k+3��° ������ �̿��ؼ� �ﰢ���� �׸�
	// ������ ���ϸ� Ȧ������ �ﰢ���� �׳� �׸���
	// ¦����° �ﰢ���� Ȧ����° �ﰢ���� ������ �� ������ ������ �ݴ�� �ٲ㼭 �̿�

	// ���� : ������ �׸��� �� ���Ǵ� ������ ������ LIST�� ���� �ξ� ����
	// LIST�� ù �ﰢ�� ���� �� �ﰢ���� �׸� �� �Ź� ������ 3���� �߰��ؾ� ������
	// STRIP�� �׳� �ϳ����� �߰��ϸ� ��

	// ���� : �����Ӱ� ������ �׸����� ����
	// ������ ���� ������ ��Ȱ���ؼ� �׸��ٺ���, ������ �ش� �������� �̿����� �� �ð������ �ǵ��� �����ؾ߸� ��
	// �ű⿡ ���� �ﰢ���� �� ������ ��� �̾ ����׸��� �����ٺ���
	// ���� ������ ������ �׸��ٴ��� �ϴ� �� �Ұ����ϰ� ������ �� ���� �ִ� �ϳ��� ������ �׸� �� �ְ� �Ǿ��ִ�.

	// ���� ���� ������ VertexShader.hlsl���� �ٷ�

}

TutorialScene::~TutorialScene()
{
	delete(list_rect);
	delete(strip_rect);
	delete(hexagon);
	VS->Release();
	PS->Release();
}

void TutorialScene::Update()
// ���� API���� �������� ��� �� �������� ȣ��ż� ���
{
}

void TutorialScene::Render()
{
	Device::Get()->Clear();			// ȭ�� �ʱ�ȭ
	UINT stride = sizeof(Vertex);   // ���ۿ� ������ ������ ������ ���� �����ϴ� ���� �ϳ� �������� �뷮 ���� ����
	UINT offset = 0;                // offset ����

	Device::Get()->GetDeviceContext()->VSSetShader(VS->GetVertexShader(), nullptr, 0);
	Device::Get()->GetDeviceContext()->PSSetShader(PS->GetPixelShader(), nullptr, 0);
	// ����̽��� ���� ���̴��� �ȼ� ���̴��� �����ϴ� ����

	Device::Get()->GetDeviceContext()->IASetInputLayout(VS->GetInputLayout());	
	// Device ���ο� ���ǵ� DeviceContext�� �����ͼ� VertexShader�� ���ǵ�inputLayout ���
	 


	// ���⼭���� �� TutorialScene���� ����� ���� ��ü���� ���� �׸��� ����
	 
    // 1. �츮�� �׸� ������ �ﰢ�� �ϳ�
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, list_rect->GetBuffer(), &stride, &offset);	// �ﰢ���� ������ �ִ� ���۸� ����̽��� ����
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(list_rect->GetType());	// �ﰢ���� �׸� Ÿ���� ����̽��� ����
	// ���� �� ��� ���� �츮�� �� ����� �������� ����

	Device::Get()->GetDeviceContext()->Draw(list_rect->GetVertexSize(), 0);	// �ﰢ���� ���� ������ ������ ���⼭ üũ�ϰ�, �� ������ ������ŭ�� �̿��� draw�� ����


	// 2. �츮�� �׸� ������ ������ �ϳ�
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, hexagon->GetBuffer(), &stride, &offset);	// �ﰢ���� ������ �ִ� ���۸� ����̽��� ����
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(hexagon->GetType());	// �ﰢ���� �׸� Ÿ���� ����̽��� ����
	// ���� �� ��� ���� �츮�� �� ����� �������� ����

	Device::Get()->GetDeviceContext()->Draw(hexagon->GetVertexSize(), 0);	// �������� ���� ������ ������ ���⼭ üũ�ϰ�, �� ������ ������ŭ�� �̿��� draw�� ����

	// STRIP
	Device::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, strip_rect->GetBuffer(), &stride, &offset);	// �ﰢ���� ������ �ִ� ���۸� ����̽��� ����
	Device::Get()->GetDeviceContext()->IASetPrimitiveTopology(strip_rect->GetType());	// �ﰢ���� �׸� Ÿ���� ����̽��� ����
	// ���� �� ��� ���� �츮�� �� ����� �������� ����

	Device::Get()->GetDeviceContext()->Draw(strip_rect->GetVertexSize(), 0);	// �ﰢ���� ���� ������ ������ ���⼭ üũ�ϰ�, �� ������ ������ŭ�� �̿��� draw�� ����


}

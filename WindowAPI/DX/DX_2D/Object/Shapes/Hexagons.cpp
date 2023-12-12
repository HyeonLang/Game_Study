#include "pch.h"
#include "Hexagons.h"

Hexagons::Hexagons(float x, float y, float size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(x, y)
{
	type = t;
	
	// ���� ��ǥ->��� ��ǥ�� ��ȯ�ϴ� �Լ�, ���� ���� ��ǥ���� ��� ��ǥ�� ��ȯ

	// ������ ���� ȭ�鿡 �׸� �� ����ϴ� ��ǥ�� ȭ�� �� ������ �������� ��� : ����Ʈ�� ���� ��� ��ǥ�� �̿��Ͽ� ����

	float screen_ratio = (float)WIN_HEIGHT / (float)WIN_WIDTH;

	// �̹����� �� ������ �ȿ��� ������ ���� ������ų ����
	// ���� �� �ȿ��� ���Ϳ� ���� �������� �Է�

	float angle = 2 * M_PI;

	for (int i = 0; i < 6; i++) 
	{
		verticies.emplace_back(Vertex(pos_x, pos_y, 0.4f, 0.4f, 1.0f));	// ���� 1
		verticies.emplace_back(Vertex(pos_x - cos(angle) * size * screen_ratio, pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f));	// ���� 2
		// �߾��� �������� �ﰢ�� ���� �������� �󸶳� ������, ��/�Ʒ��� �󸶳� ������ ����ؼ� ������ �߰��ϴ� ��
		// ó���� 2pi�� �����ؼ� �̸� ����ϸ�
		// �� ���� ó���� (pos_x - 1 * size * screen_ratio, pos_y - 0 * size)

		angle -= 2 * M_PI / 6.0f;
		// ���� �츮�� ����� �� ������
		// ���� ������ ����ؼ� ������ ���� �� �ѹ����� �� �θ��� �� �ʿ��� ���� ���� 6��

		verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio, pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);	// ���� 3
		// �̹����� angle�� 2pi�� �ƴϹǷ� �ﰢ�� ���������� ������ ��
	
	}

	

	

	//// ������ ���� ���� ����Ʈ : �ﰢ�� 6�� ���� ����Ʈ
	//vector<Vertex> vx_hexagon_list =
	//{
	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	// ���� ������ �ݵ�� �ð�������� ����

	//	// ���� ���� �� : ������ �߽� ��ǥ�� �߽��� �������� �Ѵ�.

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.7f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.6f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.6f, +0.4f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),

	//	Vertex(+0.5f, +0.5f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.5f, +0.3f, 0.4f, 0.4f, 1.0f),
	//	Vertex(+0.4f, +0.4f, 0.4f, 0.4f, 1.0f),

	//};


	// vector�� ����
	//verticies.resize(v.size());	// ���� verticies�� �����͸� ������ �� �������� �Ҵ���� ���� ����, ������ ���Ϳ� ���� ���̷� �Ҵ�.
	//copy(v.begin(), v.end(), verticies.begin());
	// copy��� �Լ��� �̿��ؼ� ���͸� v���� verticie�� ����
	// �����ϴ� ������ v�� ó������ ��������, ���縦 ������ ��ġ�� verticies�� ������

	// �������� ������� DX���� �ٷ� ��ü�� ����� ���۸� ���� : ������ InitDevice() �� ������ ������ �� �̸� �����ϴ� �κ� ����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verticies.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = verticies.data();
	// DirectX���� �̷� ���������� ����Ϸ��� �̰͵��� ���̴��� ȣȯ�Ǵ� ������ ���ۿ� �����ؼ�
	// �� ������ ������ ���̴��� �ű�� ������ ���ľ� �Ѵ�.

	Device::Get()->GetDevice()->CreateBuffer(&bd, &initData, &VB);    // ���������� ���⼭ �׸��� �׸� ������ �����ص� ���۰� ���
}

Hexagons::~Hexagons()
{
}

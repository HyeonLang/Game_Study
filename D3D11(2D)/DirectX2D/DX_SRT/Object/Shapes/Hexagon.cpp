#include "pch.h"

Hexagon::Hexagon(int x, int y, float size, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(x, y)
{
	type = t;

	// Hexagon���� �Ű� ������ ������ ����� vector�� ���� ����
	
	// ���⼭ ���� ������ �����̱� ����

	// vector<Vertex> verticies = {};
	// �������ʹ� �� ������Ʈ�� ���� �׷��� ��¿� �ʿ��� �������� �����ϰ� ������
	// ����, �����ڿ��� �� ������ �Է��ϴ� ����� ���Ѵ�
	// ������ ����, �̹� Shape���� verticies�� ����ǰ� �ʱ�ȭ�Ǿ� �����Ƿ�
	// ���� �����ڿ��� �̸� �ʱ�ȭ�� ������ ����

	// ������ �� �������� ������ǥ�� �ƴ϶� ȭ�� �߾��� �������� �ϴ� �����ǥ�� �̿�Ǵ� ��
	// ���� ������ǥ�� ����ϱ� ���ؼ� �̸� ������ ��ȯ�� �ʿ䰡 ����
	
	float screen_ratio = float(WIN_HEIGHT) / float(WIN_WIDTH);
	// �߰���, â�� ���ο� ���δ� ���� ���밪�� ���� ������ �ٸ��Ƿ�
	// �̸� �������� ���� �̸� ����� �ʿ䰡 ����

	float pos_x = ratio_pos_x(x);
	float pos_y = ratio_pos_y(y);
	// �����ڿ��� ���� �Ű������� int�̹Ƿ� ���������� ����ϴ� �� �̿��� �� ����
	// ���� float���� ��ȯ�ϴ� ������ �ʿ��ϰ�, �̸� ������ ���ο��� ����

	float angle = 2 * M_PI - 1.327f * M_PI / 6.0f;
	// M_PI = math.h�� ���ԵǾ� �ִ� �����, ������ pi�� ���� �����ص� ��
	// ������ �ﰢ�Լ��� �� ����� �����ε�, �ﰢ�Լ��� �ٷ�� �Լ����� ����ϴ� ����
	// Radian ���� �̿��ϱ� ������ �̿� �´� ������ ������ �ʿ䰡 �ִ�
	
	// angle = 2pi = 360��

	switch (type)
		// �ﰢ�� �ܿ��� �ٸ� ��¹�ĵ� �ٷﺼ ����
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		for (int i = 0; i < 6; i++)
		{
			verticies.emplace_back(pos_x, pos_y, 0.4f, 0.4f, 1.0f);
			verticies.emplace_back(
				pos_x - cos(angle) * size * screen_ratio,
				// �߾������� �ﰢ�Լ��� �̿��� ���� (�� �ȿ�����) �����ǥ�� ���ϰų� ����
				// �������� �̹� �������� X��ǥ�� ����Ѵ�
				pos_y - sin(angle) * size,
				// ���⿣ ȭ������� ������ �ʴµ�,
				// ������ ���� ȭ���� ������ ���ΰ� �� �����Ƿ�
				// �����ǥ�迡�� ���� ������ǥ �Է¿� ���� ���� ���� ������ �� �۾ƾ� ��
				0.4f, 0.4f, 1.0f);

			angle -= 2 * M_PI / 6.0f;

			verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio,
				pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);
			// ���� ������ ������ �ڿ� ���� �������� ��ġ ���

		}
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		for (int i = 0; i <= 6; i++)
		{
			verticies.emplace_back(pos_x - cos(angle) * size * screen_ratio,
				pos_y - sin(angle) * size, 0.4f, 0.4f, 1.0f);
			angle -= 2 * M_PI / 6.0f;
		}
		break;

	default:
		break;
	}

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verticies.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = verticies.data();

	Device::Get()->GetDevice()->CreateBuffer(&bd, &initData, &VB);
	// �⺻������ �������� �ԷµǴ� ����� �����ϸ� �ٸ�(Triangle) Ŭ������ ������ �ٸ� �� ������
	// �� �ٸ� Ŭ�������� �״�� ������ ������ ��Ȱ��

}

Hexagon::~Hexagon()
{
}

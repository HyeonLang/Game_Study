#include "pch.h"

Enemy::Enemy(Float2 pos, Float2 size, Float2 s, float a, float v, Matrix* parent)
	: Transform(pos, s, a, parent), velocity(v), init_pos(pos)
{
	rotate_timer = 0;

	rect = new RectUV(pos, size);

	ScratchImage image;	// ���� �̹��� ���� �ε� ���� ��ü

	LoadFromWICFile(L"Textures/images/missile.jpg", WIC_FLAGS_NONE, nullptr, image);
	// ���� ���� �ε� �Լ�
	CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);
	// ��� ���� srv�� DEVICE�� image�� �̿��ؼ� ���̴� ���ҽ� �� ����

	D3D11_SAMPLER_DESC sd = {};	// �Է¹��� �̹����� ������� ����� ������ �����ϴ� ����ü

	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// �Է¹��� �̹����� � ���͸� ������ ���ΰ�, ũ�θ�Ű�� ������ ��� �߶󳻴� ��� ����

	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// �ؽ����� U, V, W �������� 1�̻��� ������ ��� ä���� �����ϴ� ����, ū �̹����� �ٷ궧 ���

	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// �̹����� 2���̻� ��½� sd�� �ٷ�� ������ �켱������ �����Ѵ�. (���� �ö󰡴� ��)

	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;	// �Ӹ��� ������ ����, 3D���� ���� �������� ���� �ؽ�ó�� ����ȭ �� ������ ����

	// �츮�� �ҷ��� �̹����� ����̽��� ����ϱ� ����
	// ���� ���������� �����ϴ� �κ�
	DEVICE->CreateSamplerState(&sd, &sampler_state);
}

Enemy::~Enemy()
{
	delete rect;
	srv->Release();
	sampler_state->Release();
}

void Enemy::Update(DWORD time)
{
	
	rotate_timer += time;
	if (rotate_timer >= 1000)	// 1�ʰ� ������
	{
		rotate_timer -= 1000;

		std::random_device rd;
		std::mt19937_64 rng(rd());
		std::uniform_real_distribution<double> rand_dir(0.0, 2 * M_PI);
		// 0~360�� ������ ������ �����ϰ� ����

		angle = rand_dir(rng);	// ������ ����

		
	}
	Float2 cur_pos = { this->pos.x + velocity * sin(angle), this->pos.y + velocity * -cos(angle) };	
	// ���� ��ġ�� ���� ���� ���
    // ��°�������� �𸣰�����, ������� cos�� x��ǥ, sin�� y��ǥ�� ����ϴ� �� �̿�Ǿ�� �ϳ�
    // �����δ� �ݴ�� �ۿ�ǰ� ����
    // Transform�� �⺻ ȸ�� ���� �������� ���� �ִ� ������ ���� �������� ����ص״µ�
    // �̰� �ƴϾ ���� �ٸ��� �ۿ��ϰ� �ִ� �� ����

	if (cur_pos.x < 0
		|| cur_pos.x > WIN_WIDTH
		|| cur_pos.y < 0
		|| cur_pos.y > WIN_HEIGHT) // ���� ��ġ�� ��ü ȭ���� ����� ��ġ�� ���
	{
		SetPos(init_pos);
	}
	else
	{
		SetPos(cur_pos);
	}

	WorldUpdate();
}

void Enemy::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	DVC->PSSetShaderResources(0, 1, &srv);
	// �׸��� ����ϱ� ���� ����̽��� �̹����� �����ϴ� ��ü�� ����ϴ� ����
	// "���� ����� ���� �� �׸��� ����϶�"

	DVC->PSSetSamplers(0, 1, &sampler_state);
	// �̹��� �׸� �׸��� �� ���÷��� ����϶�� ���

	rect->Render();
}

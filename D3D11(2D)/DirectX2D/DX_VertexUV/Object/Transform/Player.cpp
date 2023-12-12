#include "pch.h"

Player::Player(Float2 pos, Float2 size, Float2 s, float a, Matrix* parent)
	: Transform(pos, s, a, parent)
{
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
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// �ؽ����� U, V, W �������� ������ ��� ä���� �����ϴ� ����, ū �̹����� �ٷ궧 ���

	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// �̹����� 2���̻� ��½� sd�� �ٷ�� ������ �켱������ �����Ѵ�. (���� �ö󰡴� ��)

	sd.MinLOD = 0;
	sd.MaxLOD = D3D11_FLOAT32_MAX;	// �Ӹ��� ������ ����, 3D���� ���� �������� ���� �ؽ�ó�� ����ȭ �� ������ ����

	// �츮�� �ҷ��� �̹����� ����̽��� ����ϱ� ����
	// ���� ���������� �����ϴ� �κ�
	DEVICE->CreateSamplerState(&sd, &sampler_state);

}

Player::~Player()
{
	delete rect;
	srv->Release();
	sampler_state->Release();
}


void Player::Update(Float2 pos, Float2 target)
{
	SetPos(pos);
	
	float angle = -atan2(double(pos.y) - double(target.y), double(target.x) - double(pos.x)) + M_PI_2;
	// �� �� ������ ������ ���ϴ� ����
	// Transform���� ������ 0�̶� �ϸ� �������� �ٶ󺸵��� ����, ���� ������ pi/2�� �����ش�.

	SetAngle(angle);

	WorldUpdate();
}

void Player::Render()
{
	WB->Set(world);
	WB->SetVS(0);

	DVC->PSSetShaderResources(0, 1, &srv);
	// �׸��� ����ϱ� ���� ����̽��� �̹��� ���� ��ü�� ����ϴ� ����
	 
	DVC->PSSetSamplers(0, 1, &sampler_state);
	// �̹��� �׸� �׸��� �� ���÷��� ���


	rect->Render();
}

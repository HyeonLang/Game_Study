#include "pch.h"

Triangle::Triangle(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t)
	: Shape(0.0f, 0.0f)
{
	type = t;

	// vector�� ����
	verticies.resize(v.size());
	// ���� �� �� ��ü�� ������ �ִ� ���ʹ� �����͸� ������ �� �������� �Ҵ���� ���� ����
	// �װ� �츮�� ������ ���Ϳ� ���� ���̰� �ǵ��� �뷮�� ���� �Ҵ�

	copy(v.begin(), v.end(), verticies.begin());
	// copy��� �Լ��� �̿��ؼ� ���͸� v���� verticie�� ����
	// �����ϴ� ������ v�� ó������ ��������, ���縦 ������ ��ġ�� verticies�� ������

	// ������ InitDevice() �߿��� ������ ������ �� �̸� �����ϴ� �κ��� ����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * verticies.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = verticies.data();
	// DirectX���� �̷� ���������� ����Ϸ��� �̰͵��� ���̴��� ȣȯ�Ǵ� ������ ���ۿ� �����ؼ�
	// �� ������ ������ ���̴��� �ű�� ������ ���ľ� �Ѵ�.

	Device::Get()->GetDevice()->CreateBuffer(&bd, &initData, &VB);
	// ���������� ���⼭ �׸��� �׸� ������ �����ص� ���۰� ���

}

Triangle::~Triangle()
{
}

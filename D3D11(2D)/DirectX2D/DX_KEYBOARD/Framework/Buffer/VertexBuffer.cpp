#include "pch.h"

VertexBuffer::VertexBuffer(void* data, UINT s, UINT count)
	: stride(s), offset(0)
{
	// ������ �� �������� ���۸� ����� ����ϴ� �κ��� �����ؼ�
	// �� Ŭ������ �°� ��¦ ���� ��� - (1), (2), (3) �� �κ�
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = s * count; // (1) stride : ������ �� ĭ�� �����ϴ� �뷮
	// �̸� �Է¹޾Ƽ� ����ϹǷ� Ư�� Ŭ������ ũ�⸦ ���� �ʿ� ���� �Է¹��� ���� �״�� �̿�
	// count ���� �Է¹��� �������� �� �����ͷ��� �󸶳� �Ǵ��� �𸣴�
	// �����Ϳ� �ԷµǾ� �ִ� �ڷ��� ���� ��ü�� �Ű������� �޾Ƽ� �̸� �̿�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data; // (2) ���ۿ� �Է��� �����Ͱ� ����� �ּҸ� ���⿡ �Է�

	DEVICE->CreateBuffer(&bd, &initData, &buffer); 
	// (3) ������ �̸� ��ũ�θ� �����ص� �� ������ ��ũ�η� ª�� ���̰�
	// ������(���۸�)�� �޶������� �̿� �°� �������ֱ�
}

VertexBuffer::~VertexBuffer()
{
	buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
// ���� ������Ʈ���� Scene���� �� ������ ����� ��
// DX ������ ����� �� ������ ����, �׷����� ����ϴ� ����� ���� ����� ��
// ������ ������ŭ�� ������ �׸��� ���̾��µ�
// �� �� ���� ��ϰ� ��� ��� �Է��� �� �Լ����� �ϴ� ������ ��ü
{
	DVC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	DVC->IASetPrimitiveTopology(type);
}

// �̷��� ���� Ŭ������
// ������ Shape Ŭ�������� ����ϴ� ID3D11Buffer�� ��ü�Ͽ� �̿��� ����
// -> ���� Ŭ�������� ����� ���� Scene���� ��ó���� ����� �ϴ� ���� �־�����,
// ������ �׷� �� ���� ������ ���� �ȿ��� ��� ���� ������ ���� ����ϰ� �� ��

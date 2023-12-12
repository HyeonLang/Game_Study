#pragma once
class VertexBuffer
{
private:
	ID3D11Buffer* buffer;

	UINT stride;	// �� Ŭ�������� �����ϰ� �ִ� ���۰� ��ĭ���� ����ϴ� �뷮�� ����
	// DX�ý��ۿ����� ���� ������ ���� �ϳ��� �ڷᷮ�� �𸥴�. �뷮 ��ü�� ����, �Է� �ʿ�

	UINT offset;	// ������ = ������� �������� �ε����� ���
	
public:
	VertexBuffer(void* data, UINT s, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// ������ ����ϴ� ����� ���� �� �ʿ��� ����
};



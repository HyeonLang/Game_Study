#pragma once
class ConstBuffer
{
private:
	ID3D11Buffer* buffer;

	void* data;	// ���� ��ü�� ����� ������ ��� ����
	UINT data_size;	// void ����Ʈ�� data�� ������ �𸣴� data �� ũ�� ���� ����

public:
	ConstBuffer(void* data, UINT data_szie);
	virtual ~ConstBuffer();
	// �Ҹ��ڰ� �����Լ��� ���� : ��� ���۴� �ٸ� ���ۿ� ��ӽ��� ����� ����
	// �θ�Ŭ������ �Ҹ��ڸ� ȣ��� ���ɼ��� ����
	// ���� ��ӹ��� ���� Ŭ������ �Ҹ��ڰ� Ȯ���� ȣ��� �� �ֵ��� �����Լ��� ����

	void SetVS(UINT slot);
	void SetPS(UINT slot);
	// �� ���̴� ���Կ� �ѱ� ������ ����
};


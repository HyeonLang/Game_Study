#pragma once

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	} data;
	// ���̴��� �̿��� ��, ���� ���� �����͸� MatrixBuffer�� �̿��ؼ� �ִ´�.
	// ���̴� �ʿ� ���� ������ ũ��� 16�� ������� �Ѵ�.
	// �ƴҰ�� ��� �߻�, ������ ���� �� �ִ�.(������, ����ó�� ���� �߻����� ����.)
	// Matrix = XMMATRIX �ڷ���, �̸� 16�� ����� �´� �������� �ڷ����� �ƴ�.
public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity();
		// XMMatrixIdentity = ��������� ��ȯ�ϴ� �Լ�
		// == ó�� �� MatrixBuffer�� ��������� �� �ʱⰪ���δ� 4x4 ��������� �������� �Ѵ�

		// ������� = �ִ밢��(���� ���������� ������ �Ʒ��� ���ϴ� �밢��)�� ���� ��� 1�̰�
		// ������ ���� ��� 0�� ���

		/* ������ �������� �Ǵ� ����� ������ ����
		( 1 0 0 0 )
		( 0 1 0 0 )
		( 0 0 1 0 )
		( 0 0 0 1 )

		�� ���� 4x4�ĸ� 3D ���ݿ��� ���Ǵ� �⺻���� ��� ����� 4x4�̱� ����
		WVP ��ȯ ��� ���ϰ� �������� �ʾ�����, ��ȯ ����� ���ذ����� �̸� ���� ��ġ ���� � ����� ��
		�⺻������ ���Ұ� 4���� ���͸� ����ϱ� ������, �̿� ����� ���߱� ���� 4*4 ����� ����ϴ� ��
		*/

	}
	~MatrixBuffer() {};

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value);
		// ��� ���� �����Լ�
	}
};

class ColourBuffer : public ConstBuffer	// ������ �Ѽ� ���̴��� ����ϱ� ���� ����
{
	// ������ �ȼ� ���̴��� ����ϱ� ���� ����
	// colout : ������ ����� ���̴� ���縵
public:
	struct Data
	{
		Float4 colour;
	} data;

	ColourBuffer() : ConstBuffer(&data, sizeof(data))
	{
		data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f); // �ʱⰪ ���
	}

};
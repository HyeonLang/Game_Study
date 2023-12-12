#pragma once
class Transform
	// DirectX3d ���� �Ѿ 2D Ȥ�� 3D �������� �ϳ��� ������Ʈ�� �����ϴ� �⺻ ����
	// ǥ���� ���� ���̴� ������ ��������� �ٸ� ����

	// ���α׷����� ��ü(�ν��Ͻ�)��� �θ��� ������
	// 3D �������� ������Ʈ �ϳ��� ���� �� �� Transform �⺻ ������ �Ѵ�.
	// ��� ������Ʈ�� �ϳ��� Transform�� ������.

	// 3D ����(�츮�� ��� 2D ����)���� �ϳ��� ������Ʈ�� ��� ��ġ�� ��� �������� ��� ũ�⸦ ������ �ִ�����
	// �� Transform�� �̿��ؼ� ����
{
protected:
	Float2 pos; // ������Ʈ�� ��ġ
	Float2 scale; // ������Ʈ�� ũ��(���� ũ�⸦ 1.0���� ���� �� ������ �����ϸ鼭 �󸶳� ũ�� ���� ������)
	float angle; // ������Ʈ�� �ٶ󺸰� �ִ� ����
	// 3D���ٸ� angle�� Float3�� ������ �߰����� ���� 2D�� �������

	Matrix world;	// ������Ʈ�� ���� ������ ���
					// ������Ʈ�� ���� �� ��� ���������� �� �������� ���� ����� ���·� ������ �����ϴ� ����

public:
	Transform(Float2 p, Float2 s, float a);
	~Transform();

	float GetAngle() { return angle; }
	void SetAngle(float a) { angle = a; }

	void WorldTransform(Matrix* parent = NULL);
	// �� ������Ʈ�� ����(������)�� ����. �⺻���� NULL

	Matrix* GetWorld() 
	{
		return &world;
	}

};
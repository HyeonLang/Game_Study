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
	Float3 rot;	// �� x y z �࿡ ȸ���� ����, �� �Լ��鿡 ȣȯ��Ű�� ���� Float3 ���·� �̿��ؾ��� �ʿ� ����.
	float angle; // ������Ʈ�� �ٶ󺸰� �ִ� ����
	// 3D���ٸ� angle�� Float3�� ������ �߰����� ���� 2D�� �������

	Matrix world;	// ������Ʈ�� ���� ������ ���
					// ������Ʈ�� ���� �� ��� ���������� �� �������� ���� ����� ���·� ������ �����ϴ� ����

	Vector2 pivot;	// ������Ʈ�� ����� �ٸ� ������Ʈ�� ȸ���ؾ� �� ��� ���
					// �������� �����ؾ� �� ��� ���� �����ؾ� �Ѵ�.
					// �ڱ��ڽ��� �״�� �����鼭 pivot�� ����ϴ� ������Ʈ�� ���������� ����Ѵ�.

	Matrix* parent;	// ������Ʈ�� ��ġ ���� �����ϰ� �ִ� �θ� ������Ʈ
	Matrix S, R, T, P, IP;	// SRT ��ȯ ��� ���� ������ ���� �������� �����ΰ� ���

public:
	Transform(Float2 p, Float2 s, float a, Matrix* parent = NULL );
	~Transform();

	float GetAngle() { return angle; }
	void SetAngle(float a) 
	{ 
		angle = a; 
		rot.z = a;
	}

	void SetPos(Float2 p)
	{
		pos = p;
	}
	void AddAngle(float a)
	{
		angle += a;
		rot.z = angle;
	}

	void WorldTransform(Matrix* parent = NULL);
	// �� ������Ʈ�� ����(������)�� ����. �⺻���� NULL
	void WorldUpdate();

	Matrix* GetWorld() 
	{
		return &world;
	}

};
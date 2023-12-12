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
	bool is_active;	// Ȱ��ȭ ����

	float angle; // ������Ʈ�� �ٶ󺸰� �ִ� ����

	Matrix world;	// ������Ʈ�� ���� ������ ���
					// ������Ʈ�� ���� �� ��� ���������� �� �������� ���� ����� ���·� ������ �����ϴ� ����

	MatrixBuffer* WB;

	Vector2 pivot;	// ������Ʈ�� ����� �ٸ� ������Ʈ�� ȸ���ؾ� �� ��� ���
					// �������� �����ؾ� �� ��� ���� �����ؾ� �Ѵ�.
					// �ڱ��ڽ��� �״�� �����鼭 pivot�� ����ϴ� ������Ʈ�� ���������� ����Ѵ�.

	Matrix* parent;	// ������Ʈ�� ��ġ ���� �����ϰ� �ִ� �θ� ������Ʈ
	Matrix S, R, T, P, IP;	// SRT ��ȯ ��� ���� ������ ���� �������� �����ΰ� ���

	XMFLOAT4X4 mat_world;
	Vector2 global_scale;

public:
	Float2 pos; // ������Ʈ�� ��ġ
	Float2 scale; // ������Ʈ�� ũ��(���� ũ�⸦ 1.0���� ���� �� ������ �����ϸ鼭 �󸶳� ũ�� ���� ������)
	Float3 rot;	// �� x y z �࿡ ȸ���� ����, �� �Լ��鿡 ȣȯ��Ű�� ���� Float3 ���·� �̿��ؾ��� �ʿ� ����.
	
	// 3D���ٸ� angle�� Float3�� ������ �߰����� ���� 2D�� �������

	Transform(Float2 p = Float2(0.0f, 0.0f), Float2 s = Float2(1.0f, 1.0f), float a = 0.0f, Matrix* parent = NULL);
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

	void SetActive(bool active)
	{
		is_active = active;
	}

	bool GetActive()
	{
		return is_active;
	}

	void WorldTransform(Matrix* parent = NULL);
	// ������Ʈ�� ����(������) ����. �⺻�� NULL
	void WorldUpdate();

	Matrix* GetWorld() 
	{
		return &world;
	}

	Vector2 GlobalPos()
		// ���� �׷��� ǥ�� ��ǥ ��ȯ
	{
		return Vector2(mat_world._41, mat_world._42);	
		// T ��ȯ(4��)�� x, y��ǥ ��ȯ
	} 

	Vector2 GlobalScale()
		// ���� ���� scale ��ȯ
	{
		return global_scale;
	}

};
#pragma once
// Ŭ���� �̸��� ���� Ŭ������ �Լ��� �ߺ����� �ʵ��� ����

class Hexagons : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	// �������� DX���� �׸� �� � ���� ������������ �� �������� ���� �����Ѵ�

public:
	Hexagons(float x, float y, float size,  D3D11_PRIMITIVE_TOPOLOGY t);
	~Hexagons();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
};


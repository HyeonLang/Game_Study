#pragma once
class Triangle : public Shape
{
private :
	D3D11_PRIMITIVE_TOPOLOGY type;
	// D3D11_PRIMITIVE_TOPOLOGY�� �������̹Ƿ�
	// �ش� Ÿ���� �ƿ� �� Ŭ������ ��� ������ �����صд�

public:
	Triangle(vector<Vertex> v, D3D11_PRIMITIVE_TOPOLOGY t);
	~Triangle();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	// ����� �� �ý��ۿ� � ������ �׸� ������ �̸� �������ִ� �κп�
	// �� Ŭ���� ��ü�� ������ Ÿ���� �Է��ؾ� �ϱ� ������ �̿� ������ �����ڰ� �ʿ��� ��
};
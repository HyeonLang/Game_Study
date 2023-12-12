#pragma once
class Shape
{
protected:
	vector<Vertex> verticies = {};
	// vector�� �̿��� �� ������ ����� ������ ����
	float pos_x, pos_y;
	// ������ ��ġ�� ����ص� ����
	VertexBuffer* VB;
	// ���� ������ �׷��� ��¿� �ʿ��� �����͸� �˾Ƽ� �����صε��� ���۸� �� ��ü�� ����� ����
	// ���� ������ Ŭ���� �̿�

	VertexShader* VS;
	PixelShader* PS;
	// �� ������Ʈ ���� ������ ���̴��� ������.

	ColourBuffer* CB;
	// �ȼ� ���̴��� �Է��� �� ��� ����
	// �� ������ ���� �Է��Ͽ� �ȼ� ���̴����� ó���ϴ� ���� ��Ŀ��� 
	// ���� ��ü �� ������ �� ���ۿ� ���, �ȼ� ���̴��� �Ѱ� ó��

	// ����� ���� Ŭ���� �����Ͽ� ���
public:
	Shape(float x, float y);
	~Shape();
	

	VertexBuffer** const GetBuffer() { return &VB; };
	int GetVertexSize() { return verticies.size(); };
	virtual void Render() = 0;
	// ��� ������Ʈ���� �ڱ��ڽ��� ����ϴ� ��� �Լ� : ����ϴ� ������Ʈ Ŭ�������� ����ϴ� ����� �����ϵ��� ����

	void SetColor(Float4 colour)	// �� ���ۿ� ���� �����ϴ� �Լ�
	{
		CB->data.colour = colour;
	}
};
#include "pch.h"

Transform::Transform(Float2 p, Float2 s, float a, Matrix* parent)
	: pos(p), scale(s), angle(a), parent(parent)
{
	//Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	//// ������Ʈ�� ������(ũ��)�� ��Ŀ� ����
	//// ������ 3���� �������� ���� ���̶� z������ �� 3���� ���������,
	//// �츮�� 2D�����̶� z���� ����� �ʿ䰡 ������ z���� 1.0f�� ����

	//// �� �Լ��� ������ ���� ����� ��ȯ
	///* scale.x = a, scale.y = b, scale.z = c
	//( a 0 0 0 )
	//( 0 b 0 0 )
	//( 0 0 c 0 )
	//( 0 0 0 1 )
	//*/
	//Matrix R = XMMatrixRotationZ(angle);
	//// ������Ʈ�� ȸ������ ��Ŀ� ����
	//// ���������� ������ X��, Y��, Z�� ������ ���� ȸ���� ����ؾ� ������
	//// ���� 2D�̹Ƿ� �츮�� ȭ���� ���� ����, �� Z���� ȸ���� ����ϸ� ��

	///* angle = a
	//( cos(a) -sin(a) 0 0 )
	//( sin(a) cos(a)  0 0 )
	//(   0       0    1 0 )
	//(   0       0    0 1 )
	//*/
	//Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	//// ������Ʈ�� ������ ��Ŀ� ����
	//// �׳� ��ǥ�� ���� �̵��� �� ����� ���� �����Ѵٰ� ���� ����
	///* pos.x = a, pos.y = b, pos.z = c
	//( 1 0 0 0 )
	//( 0 1 0 0 )
	//( 0 0 1 0 )
	//( a b c 1 )
	//*/

	//// �� �������� � ����� ������������ �˾Ƶ� �ʿ䰡 �ֱ� ��
	//// �� �ڼ��� ������ ������ https://pjnull.tistory.com/6 ���� Ÿ ����Ʈ�� ������ ����

	//world = S * R * T;

	world = XMMatrixIdentity();	// world�� �����ϴ� �κ��� worldUpdate�ʿ��� ����

}

Transform::~Transform()
{
}

void Transform::WorldTransform(Matrix* parent)
// ������ ������ ���� �� ������Ʈ
// �� ������Ʈ�� �ٸ� ������Ʈ�� ��ġ�� �����ϴ� ������Ʈ�� ���
// �� �����ϰ� �ִ� ������Ʈ�� "�θ�"�μ� �Ǵ��Ͽ� "�θ�"�� ���� ��ȯ�����
// �� Ʈ�������� ���� ��Ŀ� ���ؼ� �����Ű�� ��

// ������ �������� �������� ��Ŀ� ���� 3���� ������ ��ü�� ��ǥ�� ���� �ٸ��� ǥ���� �� �ִµ�
// �� �������� ���� ��� ��ǥ�� �ƴ� ���� ��ǥ�� ���ϴ� �����̶�� ���� ����
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(angle);
	Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	world = S * R * T;
	// ��������� �����ڿ���ó�� �з����͵��� ���� �� Ʈ�������� ��ȯ ����� ���� ��


	// ���� �θ� �����ϴ� Ʈ�������̶��
	if (parent != NULL)
		world *= *parent;
	// �θ��� SRT ���� ��ȯ ����� �� Ʈ�������� �����ؼ� ���� ���������� ��ǥ���� ���
}

void Transform::WorldUpdate()
{
	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	R = XMMatrixRotationZ(angle);
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);	// pivot�� �����͸� ���� SRT ��ȯ ����� ����ϱ� ���� ���� ���
	IP = XMMatrixInverse(NULL, P);	// �Էµ� ����� ���Լ�

	world = IP * S * R * T * P;
	// �ǹ� ���� ����İ� ����� �յڿ� �����־�� �Ѵ�.
	if (parent != NULL)
		world *= *parent;
}

// 06_destruction_order_of_derived_class.cpp

/*
	������ ������ �������� �Ҹ��� ȣ��
	���� ������ ��ü�� �ٸ� ��ü�� �� ���� ���踦 �ΰ����� Ȯ���� ����.
	���� ������ �������� ��ü�� �����ϴ� ���� �����ϴ�.
*/
#include<iostream>
using namespace std;

class A
{
public:
	A() { cout << "A constructor" << endl; }
	~A() { cout << "A destructor" << endl; }

private:
	int a;
};

class B : public A
{
public:
	B() { cout << "B constructor" << endl; }
	~B() { cout << "B destructor" << endl; }

private:
	double b;
};

int main() {

	B b;

	/*
		�е�
		- Ŭ������ ����ü�� �е� ����Ʈ�� �߰��Ͽ� cpu�� �����ϱ� �����ϰ� ���ִ� ���
		- CPU�� �����͸� ���� �� �ڷ����� �߷� ���� �����Ϳ� �ι� �����ϴ� ���� ����
		- �Ϲ������� ���� ū ��� ���� ũ�⿡ ���� �е� ����Ʈ�� �߰��Ѵ�.
	*/

	// a : 4byte
	sizeof(A);	// a a a a
	// b : 8byte + a : 4byte + padding : 4byte
	sizeof(B);	// a a a a �� �� �� �� b b b b b b b b : ���� byte ������ �б� ���� ���̵����� ���� : padding

	class P1 {  
		char c;
		short s1;
		short s2;
	};
	sizeof(P1); // c �� s1 s1 s2 s2 : 6byte
	//short���� ���� �е�����Ʈ �߰�

	class P2 { 
		char c1;
		double d;
		char c2;
	};
	sizeof(P2); // c1������������  d d d d d d d d c2������������ : 24byte
	//double���� ���� �е�����Ʈ �߰�


	return 0;
}
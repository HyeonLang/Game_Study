// 18_dynamic_casting.cpp
// ���� ĳ����

#include<iostream>
using namespace std;

class Base
{
public:
	virtual void Print() { cout << "Base" << endl; }
public:
	int i = 0;
};

class Derived1 : public Base
{
public:
	virtual void Print() override { cout << "Derived1" << endl; }
public:
	int j = 1;
};

class Derived2 : public Base
{
public:
	virtual void Print() override { cout << "Derived2" << endl; }
public:
	int k = 2;
};

void DoSomething(Base* b) 
{
	{
		// static_cast : ������ Ÿ�ӿ� �ڷ����� ĳ���� ������ �������� Ȯ����.
		// Base* -> Derived2* �� �ٿ� ĳ���� ������ �����̹Ƿ� ���
		// ������ Ÿ�Ӷ� ĳ���� ���ɿ��θ� �Ǵ��ϹǷ� ������ ���� �����͸� Ȯ������ ���� �������� ������
		//Derived2* base_to_d2 = static_cast<Derived2*>(b);

		// Derived1 �޸� : i i i i j j j j 
		// Derived2 �޸� : i i i i k k k k
		//base_to_d2->k = 888;
	}

	{
		// dynamic_cast : ��Ÿ�ӿ� �ڷ����� ����Ű�� �����Ͱ� ���� ĳ���� ������ ��ü���� Ȯ���Ѵ�.
		// �̹� ���, ���� Ÿ���� Derived1 �̹Ƿ� ĳ���� ����� -> ���н� nullptr ��ȯ
		// ���� �޸𸮸� Ȯ���ϹǷ� ���������� static_cast���� ���� �� ������� �ʴ´�.
		// static_cast�� ����԰� ���ÿ� ���� Ÿ���� ������ �� �ִ� id���� �ο��Ͽ� �˻��Ѵ�.
		Derived2* base_to_d2 = dynamic_cast<Derived2*>(b); // ������ b�� ������ Ȯ���Ͽ� ĳ���� ���θ� �Ǵ�
		base_to_d2->k = 888; //error!
	}
}


int main()
{
	// ��ĳ����
	Derived1 d1;
	Base* base = &d1;

	// **�ٿ� ĳ������ ����� ����ȯ�� ������Ѵ�.**
	Derived1* base_to_d1 = static_cast<Derived1*>(base);
	base_to_d1->Print();

	DoSomething(&d1);	// Derived1 ���� �Ѱ�µ� �Ű��������� Base�� ��ĳ���� �� �� Derived2 ������ �ٿ� ĳ����
						// DoSomething ������ k�� ����

	cout << d1.j << endl;	// Derived2 ���� k���� ��µ�.
							// �޸��� ������� ��ġ�� j,k�� ���� �ڷ����� ���� �Ͼ ��.

	return 0;
}


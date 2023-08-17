// 08_overriding_and_final.cpp

/*
	Overriding
	- �Ļ� Ŭ������ ��� Ŭ�������� ��ӹ��� �Լ����� �Ļ� Ŭ�������� *������* �ϴ� ��.

	- **���� Ÿ�԰� �Ű����� ������ ���� ��ġ**�ؾ� �Ѵ�.

	- �������̵��� ���Ŭ������ �Լ��� �������� �Ļ�Ŭ������ �Լ��� ȣ��ȴ�.

	- �ܼ��� �Լ��� �������̵��� ���, ��ĳ���ý� �Ļ� Ŭ������ �Լ��� �ƴ� ��� Ŭ������ �Լ��� ȣ��ȴ�.
	�� ������ c++�����Ϸ��� ������ ����Ű�� ��ü�� �ڷ����� �������� �ϴ°� �ƴ϶� *������ ������ �ڷ����� ����*���� �ϱ� �����̴�.
	*** virtual *** Ű���� ���� �ذ� ����
	
	- virtual
		�� �ڽ��� ȣ���ϴ� ��ü�� **���� Ÿ��**�� �°� �Լ��� ȣ���� �� �ְ� ���ִ� Ű����
		�� ��� Ŭ������ �Լ��� Ű���带 �߰����ָ� *�Ļ�Ŭ������ �ڵ����� ���*�ȴ�.

*/

#include <iostream>
using namespace std;

class A {
public:
	// virtual Ű���尡 ���Ե� �Լ� : ���� �Լ�
	virtual void Print(int x) { cout << "A" << endl; }
private:
	int i = 0;
};

class B : public A {
public:
	/*
		�����ε� : �ߺ��� �̸��� ������ �Լ����� �Ű����� ���̷� �����Ͽ� �پ��ϰ� ����� ���
		�������̵� : ��ӹ��� �Լ����� �������Ͽ� ���� ����� ��

		�������̵��� �θ��� �Լ��� �������Ͽ� ����ϴ� ���̱� ������ �θ��� �Լ� ���¿� ��ġ.
	*/
	void Print(int x) override /*final*/ { cout << "B" << endl; } // ���� �Լ��� overrding : �Լ��� ���� ����

	/*
		override - �������̵� Ű����
		- �Ļ� Ŭ�������� �������̵��� �Լ��� ���� �� �ִ�.
		- �������̵��� ������ �Լ����� �Ǵ����ְ�(�´� ���°� �ִ���) ���ٸ� ���� �߻�
		- �������̵��� �� �Լ����� ���������� ǥ���Ѵ�. -> �ڵ� �������� ����.
	*/
};

// final : Ŭ������ ��ӽ�ų �� ���� �����ϴ� Ű����, �Լ��� ���̸� �ش� �Լ��� �Ļ�Ŭ�������� �������̵� ���� �ʰ� ����
class C final : public B {
public:
	// ��ӹ��� �޼��忡 final Ű���尡 �����Ѵٸ� �������̵� �Ұ�
	void Print(int x) override { cout << "C" << endl; }
private:
};

int main() {
	A a;
	B b;
	C c;

	a.Print(1);
	b.Print(1);
	c.Print(1);

	cout << "=================" << endl;

	//�� ĳ����
	A& ab = b; 
	A& ac = c;

	a.Print(0);
	ab.Print(0);
	ac.Print(0);

	return 0;
}
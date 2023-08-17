// 05_class_template_specialization.cpp
// Ŭ���� ���ø� Ư��ȭ

#include <iostream>
using namespace std;

template<class T>
class A {
public:
	A(const T& input) {}

	void DoSomething() {
		cout << typeid(T).name() << endl;
	}

	void Test() {}
};

template<>
class A<char> { //<char> �ڷ��� Ŭ���� ���ø� Ư��ȭ
public:
	A(const char& input) {}

	void DoSomething() {
		cout << "char class" << endl;
	}
};

int main() {

	A<int> a1(10);
	A<float> a2(10.0f);
	A<char> a3('a');

	a1.DoSomething();
	a2.DoSomething();
	a3.DoSomething();

	a1.Test();
	a2.Test();
	// ���ø� Ŭ������ ����� �ٸ��� ���� �� �ִ�.
	//a3.Test(); // Ư��ȭ�� A<char>�� Test() ����� ������ ���� ����.


	return 0;
}
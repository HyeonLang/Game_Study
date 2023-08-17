// 05_class_template_specialization.cpp
// 클래스 템플릿 특수화

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
class A<char> { //<char> 자료형 클래스 템플릿 특수화
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
	// 템플릿 클래스는 멤버도 다르게 가질 수 있다.
	//a3.Test(); // 특수화한 A<char>는 Test() 멤버를 가지고 있지 않음.


	return 0;
}
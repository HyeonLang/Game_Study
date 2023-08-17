// 11_virtual_function_and_polymorphism.cpp

#include <iostream>
using namespace std;

/*
	A의 가상함수 테이블 : 객체가 가진다.
	A::Print1()
	A::Print2()
	A::Print3()
	A::Print4()
*/
class A {
public:
	void Print() { cout << "A" << endl; }
	virtual void Print1() { cout << "A1" << endl; }
	virtual void Print2() { cout << "A2" << endl; }
	virtual void Print3() { cout << "A3" << endl; }
	virtual void Print4() { cout << "A4" << endl; }
};

/*
	B의 가상함수 테이블 : 객체가 가진다.
	B::Print1()
	B::Print2()
	B::Print3()
	A::Print4()
*/
class B : public A {
public:
	void Print() { cout << "B" << endl; }
	virtual void Print1() { cout << "B1" << endl; }
	virtual void Print2() { cout << "B2" << endl; }
	virtual void Print3() { cout << "B3" << endl; }
};

/*
	C의 가상함수 테이블 : 객체가 가진다.
	C::Print1()
	C::Print2()
	B::Print3()
	A::Print4()
*/
class C : public B {
public:
	void Print() { cout << "C" << endl; }
	virtual void Print1() { cout << "C1" << endl; }
	virtual void Print2() { cout << "C2" << endl; }
};


/*
	B의 가상함수 테이블 : 객체가 가진다.
	C::Print1()
	C::Print2()
	B::Print3()
	D::Print4()
*/
class D : public C {
public:
	void Print() { cout << "D" << endl; }
	virtual void Print1() { cout << "D1" << endl; }
	virtual void Print4() { cout << "D4" << endl; }
};


int main()
{
	// 각 클래스에 맞는 메서드 출력한다. 
	A a;
	a.Print1();

	B b;
	b.Print1();

	C c;
	c.Print1();

	D d;
	d.Print1();
	
	/*
		업 캐스팅 시 오버라이딩한 파생 클래스의 메서드가 가려져 제대로 출력되지 않음.
		-> 상위 클래스의 오버라이딩할 메서드에 virtual 키워드를 붙여 해결이 가능.
		virtual 키워드는 객체에 가상함수 테이블을 생성하여 각 객체의 원래 자료형에 맞는
		메서드를 호출 시킨다.

		virtual function tabel - 가상 함수 테이블

		- virtual 키워드가 붙은 메서드는 가상함수가 되어 가상 함수 테이블에 추가되고
		가상 함수 테이블을 통해 호출 된다.

		- 파생 클래스에서 기반 클래스의 가상 함수를 오버라이딩하면 가상 함수 테이블이 가리키던
		가상 함수 주소를 파생 클래스가 오버라이딩한 함수로 교체한다.

		- 클래스 마다 1개만 존재한다. -> 여러 객체가 있어도 하나의 가상 함수 테이블을 가리킨다.

		// 과제 : virtual 키워드와 가상 함수 테이블 조사
	*/

	A& ref_b = b;
	A& ref_c = c;
	A& ref_d = d;

	cout << "########## A" << endl;
	a.Print();
	a.Print1();
	a.Print2();
	a.Print3();
	a.Print4();

	cout << endl << "########## B" << endl;
	ref_b.Print();
	ref_b.Print1();
	ref_b.Print2();
	ref_b.Print3();
	ref_b.Print4();

	cout << endl << "########## C" << endl;
	ref_c.Print();
	ref_c.Print1();
	ref_c.Print2();
	ref_c.Print3();
	ref_c.Print4();

	cout << endl << "########## D" << endl;
	ref_d.Print();
	ref_d.Print1();
	ref_d.Print2();
	ref_d.Print3();
	ref_d.Print4();

	cout << endl << "############" << endl;

	//d1, d2 두 객체의 가상 함수 테이블 주소가 같다.
	D d1;
	D d2;

	return 0;
}

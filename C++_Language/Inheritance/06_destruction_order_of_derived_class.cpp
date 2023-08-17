// 06_destruction_order_of_derived_class.cpp

/*
	생성자 순서의 역순으로 소멸자 호출
	먼저 생성된 객체는 다른 객체와 더 많은 관계를 맺고있을 확률이 높다.
	따라서 생성의 역순으로 객체를 해제하는 것이 안전하다.
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
		패딩
		- 클래스가 구조체의 패딩 바이트를 추가하여 cpu가 접근하기 용이하게 해주는 기법
		- CPU가 데이터를 읽을 때 자료형이 잘려 같은 데이터에 두번 접근하는 것을 방지
		- 일반적으로 가장 큰 멤버 변수 크기에 맞춰 패딩 바이트를 추가한다.
	*/

	// a : 4byte
	sizeof(A);	// a a a a
	// b : 8byte + a : 4byte + padding : 4byte
	sizeof(B);	// a a a a ㅁ ㅁ ㅁ ㅁ b b b b b b b b : 같은 byte 단위로 읽기 위해 더미데이터 삽입 : padding

	class P1 {  
		char c;
		short s1;
		short s2;
	};
	sizeof(P1); // c ㅁ s1 s1 s2 s2 : 6byte
	//short형에 맞춰 패딩바이트 추가

	class P2 { 
		char c1;
		double d;
		char c2;
	};
	sizeof(P2); // c1ㅁㅁㅁㅁㅁㅁ  d d d d d d d d c2ㅁㅁㅁㅁㅁㅁ : 24byte
	//double형에 맞춰 패딩바이트 추가


	return 0;
}
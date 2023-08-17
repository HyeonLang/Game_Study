// 18_dynamic_casting.cpp
// 동적 캐스팅

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
		// static_cast : 컴파일 타임에 자료형이 캐스팅 가능한 형태인지 확인함.
		// Base* -> Derived2* 로 다운 캐스팅 가능한 형태이므로 허용
		// 컴파일 타임때 캐스팅 가능여부를 판단하므로 빠르나 실제 데이터를 확인하지 못해 안정성이 떨어짐
		//Derived2* base_to_d2 = static_cast<Derived2*>(b);

		// Derived1 메모리 : i i i i j j j j 
		// Derived2 메모리 : i i i i k k k k
		//base_to_d2->k = 888;
	}

	{
		// dynamic_cast : 런타임에 자료형이 가리키는 데이터가 실제 캐스팅 가능한 객체인지 확인한다.
		// 이번 경우, 실제 타입이 Derived1 이므로 캐스팅 불허용 -> 실패시 nullptr 반환
		// 실제 메모리를 확인하므로 안전하지만 static_cast보다 느려 잘 사용하지 않는다.
		// static_cast를 사용함과 동시에 실제 타입을 구분할 수 있는 id값을 부여하여 검사한다.
		Derived2* base_to_d2 = dynamic_cast<Derived2*>(b); // 데이터 b를 실제로 확인하여 캐스팅 여부를 판단
		base_to_d2->k = 888; //error!
	}
}


int main()
{
	// 업캐스팅
	Derived1 d1;
	Base* base = &d1;

	// **다운 캐스팅은 명시적 형변환을 해줘야한다.**
	Derived1* base_to_d1 = static_cast<Derived1*>(base);
	base_to_d1->Print();

	DoSomething(&d1);	// Derived1 형을 넘겼는데 매개변수에서 Base로 업캐스팅 된 후 Derived2 형으로 다운 캐스팅
						// DoSomething 내에서 k값 변경

	cout << d1.j << endl;	// Derived2 형의 k값이 출력됨.
							// 메모리의 상대적인 위치가 j,k가 값고 자료형도 같아 일어난 일.

	return 0;
}


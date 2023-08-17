// 17_object_slicing_and_reference_wrapper.cpp
// 객체 슬라이싱과 참조 wrapper


/*
   Object Slicing - 객체 슬라이싱 : 큰 자료형의 값을 작은 자료형에 담으면 잘림현상이 나타날 수 있다.
   - 파생 클래스(큰 자료형)의 인스턴스를 기반 클래스(작은 자료형)의 인스턴스로 복사할 때 일어난다.
   - 파생 클래스가 가진 정보가 손실된다.
*/

#include<iostream>
#include<vector>
#include<functional> // reference_wrapper 기능이 들어있다.

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
	int k = 1;
};

void DoSomething(Base b /*Base& b*/)
{
	b.Print();
}

int main()
{
	// 1. reference : 업캐스팅
	Derived1 d1;
	Base& ref1 = d1;// reference : d1을 Base 형태로 참조, 메모리는 유지하면서 크기만 작게 사용함.
	ref1.Print();	// "Derived1" 

	// 2. copy : d1의 Base 까지의 내용만 복사하여 새 메모리 생성
	Base base = d1;	// copy : d1이 가진 Derived1의 멤버 데이터가 잘림 : object_slicing
	base.Print();	// "Base"

	// 매개변수의 타입이 copy, reference 형태인지에 따라 결과가 달라짐
	DoSomething(d1); //Base b / Base& b

	// 3.
	// 손실없이 vector에 넣고 싶을 때 
	Derived1 derived1;
	Derived1 derived2;
	Derived2 derived3;
	Derived2 derived4;

	// copy 형태라 문제가 생김
	//vector<Base> my_vec;

	// -> 참조하는 형태로 수정
	// * 사용 
	vector<Base*> my_vec1; // 동적배열인 vector에서는 참조사용이 보통 안됨.

	my_vec1.push_back(&derived1);
	my_vec1.push_back(&derived2);
	my_vec1.push_back(&derived3);
	my_vec1.push_back(&derived4);

	for (auto& vec : my_vec1)
		vec->Print();

	// &는 백터에 안들어감 -> 쓰고싶으면 reference_wrapper나 포인터를 사용하자
	// reference_wrapper 사용 : 템플릿 클래스

	vector<reference_wrapper<Base>> my_vec2;

	my_vec2.push_back(derived1);
	my_vec2.push_back(derived2);
	my_vec2.push_back(derived3);
	my_vec2.push_back(derived4);

	for (auto& vec : my_vec2)
		vec.get().Print(); //get()

	return 0;
}
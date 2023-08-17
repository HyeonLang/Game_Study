// 09_Covariant.cpp
// 공변반환형

/*
   Covariant : 공변반환형
   - 자신의 참조를 반환하는 경우 상속관계에서 같은 형태의 함수로 인정되는 것
   - is a 관계이기 때문에 자신의 참조를 리턴할 때 같은것으로 인식한다.
   - 반환값을 다르게해도 오버라이딩이 가능한 방법
*/

#include<iostream>
using namespace std;

class A
{
public:
	virtual A* GetThisPointer() { cout << "A" << endl; return this; }
};

class B : public A
{

public:
	// 공변반환형 : 상속관계, is-a 관계 이므로 자기자신을 리턴 할 경우 반환형이 달라도 오버라이딩이 가능하다. 
	B* GetThisPointer() override { cout << "B" << endl; return this; }

};
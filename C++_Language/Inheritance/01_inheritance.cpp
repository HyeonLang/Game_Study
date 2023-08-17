// 01_inheritance.cpp

/*
	Inheritance - 상속
	 - 다른 클래스의 내용을 그대로 포함할 수 있는 기능(유지보수가 쉬워진다.) (단 남발시 관리 어려움.)
	 - 보통 최대 3단계 까지만 사용한다.
	 - 공통된 동작을 모듈화하여 코드를 재사용 하기에 유리하다.
	 - 파생 클래스를 만들어 기반 클래스의 기능을 수정/확장하기에 용이
	 - 코드의 중복을 줄여 간소화 할 수 있다. (getter, setter 등)
*/



#include<iostream>
using namespace std;


// Base class - 기반 클래스
class Base
{
public:
	int GetA() const
	{
		cout << "Base::GetA" << endl;
		return a;
	}
	void SetA(const int& a) { this->a = a; }

private:
	int a;

public:
	int b;
	int c;
};

// Derived class - 파생 클래스, base class의 멤버를 모두 상속받는다.
class Derived : public Base
{
public:
	int GetA() const
	{
		cout << "Derived::GetA" << endl;

		// 상속받은 멤버를 자식 클래스에서 사용가능
		c; // Base::c

		// 기반/파생 클래스의 멤버의 이름이 중복되면 파생 클래스의 멤버가 우선시 된다.
		b; // Derived::b
		Base::b;	// 네임 스페이스를 사용하여 기반 클래스 멤버에 접근가능
		Derived::b;

		// 기반 클래스의 private 멤버는 상속이 되어도 접근이 안된다.
		// 자식 클래스에서는 protected나 public 멤버만 접근 가능
		//return a;

		return Base::GetA();

		// __super로 부모 클래스 표현가능, VC 전용
		//__super::GetA();
	}

private:
	int b;
};

int main()
{
	Derived d;

	// 기반 클래스에서 상속받은 멤버 함수 
	d.SetA(10);

	// 기반/파생 클래스의 멤버가 중복될경우 파생 클래스의 멤버가 우선시 된다.
	// 파생 클래스의 멤버를 우선해서 호출할 뿐 기반 클래스의 멤버도 모두 가지고 있다.
	d.GetA();

	// 네임스페이스를 사용하여 숨겨진 부모의 멤버에 접근가능
	d.Base::GetA();

	return 0;
}
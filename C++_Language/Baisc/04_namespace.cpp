// 04_namespace.cpp

/*
	이름 공간 (namespace)
	- 정의된 객체에 대해 소속을 정해주는 것
	- std::cout, std::cin 여기서 std가 cout, cin의 이름 공간
	- 이름이 같아도 이름공간이 다르면 다른 객체로 인식한다.
	- 변수나 함수의 이름이 겹치는 경우를 해결할 수 있다.

	선언
	namespace 공간의이름
	{
		멤버
	}

	접근법

	공간이름::멤버

	예)

	namespace a
	{
		int b;
	}

	a::b = 10;
	- 이름공간 a에 있는 변수 b에 접근하여 10대입
*/

#include<iostream>

namespace my_namespace_1
{
	int a; // my_namespace_1::a

	void DoSomething(){} // my_namespace_1::DoSomething()

	// 이름공간을 중첩하여 사용가능
	namespace DIDI
	{
		namespace TITI
		{
			namespace RURU
			{
				int c; // my_namespace_1::DIDI:TITI::RURU::c
			}
		}
	}
}

// 분리해서 사용해도 같은 공간으로 소속된다
namespace my_namespace_1
{
	int hello;
}

// c++17 가능
//namespace my_namespace_1::DIDI::TITI::RURU
//{
//	int test;
//}


namespace my_namespace_2
{
	int a;
	void DoSomething() {}
}

/*
	using namespace 이름공간
	- 해당 이름공간을 선언한 영역내에서 사용하지 않고도 접근이 가능하다.
*/

using namespace std;

int main()
{
	//a; // error, 선언되어있지않음

	// 이름공간으로 중복된 이름으로 변수를 선언가능
	my_namespace_1::a = 10;
	my_namespace_2::a = 15;

	cout << my_namespace_1::a << endl;
	cout << my_namespace_2::a << endl;

	// using namespace를 전역에 선언하게되면 중복문제를 일으킬 가능성이 많이 생기니
	// 가능하다면 사용한 영역내에 선언하는게 좋다.
	{
		using namespace my_namespace_1;
		using namespace my_namespace_2;

		//a; // ambiguous : 모호성 문제 발생

		my_namespace_1::a;
	}

	return 0;
}
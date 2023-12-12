// 10_exception_handling_5.cpp

#include<iostream>
using namespace std;

// {} 괄호를 생략하고 만든 것 -> Function Try
void DoSomething()
try
{
	throw - 1;
}
catch (...)
{
	cout << "Catch int DoSomething()" << endl;
}


//1. 2.
class A
{
public:
	A(int x)
	{
		if (x <= 0)
			throw - 1;
	}
private:
	int x;
};

class B : public A
{
public:
	//1.
	//B(int x) : A(x)
	//{
	//	//1. A생성자에서 예외를 던져 잡히지 않음
	//	try
	//	{
	//		// 여기에서 A()가 호출되야 하는데 문법상 안됨
	//		// -> function try로 해결가능
	//	}
	//	catch (...)
	//	{
	//		cout << "Catch in B()" << endl;
	//	}
	//}

	//2.
	// A생성자에서 throw한것을 바로 받을 수 있음
	B(int x) try : A(x)
	{

	}
	catch (...)
	{
		cout << "Catch in B constructor" << endl;

		// 생성자를 function try로 만들면 적지 않아도 포함이 된다.
		// 적혀있는것처럼 동작한다고 생각하는게 좋음
		// throw; 
	}

private:
};

int main()
{
	//1.
	try
	{
		B b(0);
	}
	catch (...)
	{
		cout << "Catch in main()" << endl;
	}

	return 0;
}
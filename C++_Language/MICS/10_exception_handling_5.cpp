// 10_exception_handling_5.cpp

#include<iostream>
using namespace std;

// {} ��ȣ�� �����ϰ� ���� �� -> Function Try
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
	//	//1. A�����ڿ��� ���ܸ� ���� ������ ����
	//	try
	//	{
	//		// ���⿡�� A()�� ȣ��Ǿ� �ϴµ� ������ �ȵ�
	//		// -> function try�� �ذᰡ��
	//	}
	//	catch (...)
	//	{
	//		cout << "Catch in B()" << endl;
	//	}
	//}

	//2.
	// A�����ڿ��� throw�Ѱ��� �ٷ� ���� �� ����
	B(int x) try : A(x)
	{

	}
	catch (...)
	{
		cout << "Catch in B constructor" << endl;

		// �����ڸ� function try�� ����� ���� �ʾƵ� ������ �ȴ�.
		// �����ִ°�ó�� �����Ѵٰ� �����ϴ°� ����
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
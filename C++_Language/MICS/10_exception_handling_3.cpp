// 10_exception_handling_3.cpp


// exception_class_and_inheritance.cpp

#include<iostream>
using namespace std;

// ���� ��ü�� ���� ����� �����Ҽ��� �ִ�.
//2.
class Exception
{
public:
	void Report() const
	{
		cerr << "Exception report" << endl;
	}

private:
};

//3. 4.
class ArrayException : public Exception
{
public:
	void Report() const
	{
		cerr << "ArrayException report" << endl;
	}
};

// 1. 2. 3. 4.
class MyArray
{
public:
	int& operator [](const int& index)
	{
		//1.
		//if (index < 0 || index >= 5) throw - 1;

		// 2.
		// ���ܸ� ��ü ���·� ����
		//if (index < 0 || index >= 5) throw Exception(); 

		// 3. 4.
		// ��ĳ������ �̿��� ���� ��¿� ��쿡 ���� 
		// �ٸ� ������ ��ų �� �ִ�. 
		if (index < 0 || index >= 5) throw ArrayException();

		return data[index];
	}

private:
	int data[5];
};

void DoSomething()
{
	cout << "DoSomething Begin" << endl;

	MyArray my_arr;

	try
	{
		my_arr[100];
	}
	//1.
	catch (const int& x)
	{
		cerr << "Exception : " << x << endl;
	}

	//2.
	//catch (const Exception& e)
	//{
	//	e.Report();
	//}

	//3.
	//catch (const ArrayException& e)
	//{
	//	e.Report();

	//	/*
	//		rethrow
	//		- �����Ŀ� �ٽ� ������ ��
	//		- catch�� �Ʒ��� �־ �Լ��� Ż���Ѵ�
	//			-> if else��� �����ϸ� ��
	//	*/
	//	throw e; 
	//}
	// 
	//4.
	catch (const Exception& e) // �Ļ� Ŭ������ ��ĳ���� �Ǿ� ������. 
	{
		e.Report();

		// ������ ��ĳ����(Exception����) �Ǿ��
		// main�� �ִ� ���� catch�� ArrayException���¶� ���� ����
		//throw e;

		// throw�� ���� ���� ���·� ����
		throw;
	}

	cout << "DoSomething End" << endl;
}

int main()
{
	try
	{
		DoSomething();
	}
	catch (ArrayException& e)
	{
		e.Report();
	}

	return 0;
}
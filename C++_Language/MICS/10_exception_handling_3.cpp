// 10_exception_handling_3.cpp


// exception_class_and_inheritance.cpp

#include<iostream>
using namespace std;

// 예외 객체를 따로 만들어 관리할수도 있다.
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
		// 예외를 객체 형태로 날림
		//if (index < 0 || index >= 5) throw Exception(); 

		// 3. 4.
		// 업캐스팅을 이용해 오류 출력에 경우에 따라 
		// 다른 동작을 시킬 수 있다. 
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
	//		- 잡은후에 다시 던지는 것
	//		- catch가 아래에 있어도 함수를 탈출한다
	//			-> if else라고 생각하면 됨
	//	*/
	//	throw e; 
	//}
	// 
	//4.
	catch (const Exception& e) // 파생 클래스가 업캐스팅 되어 잡힌다. 
	{
		e.Report();

		// 나갈때 업캐스팅(Exception형태) 되어나감
		// main에 있는 다음 catch가 ArrayException형태라 잡지 못함
		//throw e;

		// throw로 쓰면 원래 형태로 나감
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
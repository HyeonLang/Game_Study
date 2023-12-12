// 10_exception_handling_2.cpp

#include<iostream>
using namespace std;

/*
	Stack Unwinding : 스택 되감기
	- 예외를 throw할 경우 던진 예외를 catch할 수 있을때까지 스택을 되감는것
*/

void first();
void second();
void third();
void last();

// exception specifier

// 모든 형태의 예외를 throw할 수 있다는 표현
//void Test() throw(...);
//void Test() noexcept(false);

// int형의 예외를 throw할 수 있다는 표현
// 아래와 같이 적을경우 noexcept(false);로 해석하고 17버전 한정 : 컴파일러가 C5040 에러를 실행함
// 그렇기 때문에 위와 같은 형태로 쓰는것을 추천함
//void Test() throw(int); 

// 예외를 throw하지 않겠다는 표현
//void Test() noexcept;
//void Test() noexcept(true);

// 이것도 예외를 throw하지 않겠다는 표현이지만 모드에 따라서 동작하지 않을수도 있으니
// 위와 같은 형태로 사용하는걸 추천한다.
//void Test() throw(); 

int main()
{
	cout << "Start" << endl;

	try
	{
		first();
	}
	catch (char)
	{
		cerr << "main caught char exception" << endl;
	}
	catch (...)// catch-all handlers 모든 예외 타입을 잡을수 있음
	{
		cerr << "main caught elipses exception" << endl;
	}

	cout << "End main" << endl;
	return 0;

	return 0;
}

void first()
{
	cout << "first" << endl;

	try
	{
		second();
	}
	catch (int)
	{
		cerr << "first caught int exception" << endl;
	}

	cout << "End first" << endl;
}

void second()
{
	cout << "second" << endl;

	try
	{
		third();
	}
	catch (double)
	{
		cerr << "second caught int exception" << endl;
	}

	cout << "End second" << endl;
}

void third()
{
	cout << "third" << endl;

	last();

	cout << "End third" << endl;

}

void last()
{
	cout << "last" << endl;

	cout << "Throw exception" << endl;
	throw - 1;
	// throw하는 순간 아래 코드 실행 안하고 종료
	// 종료후 third로 이동  -> catch가 없음 
	// 종료후 second로 이동 -> double형이라 못잡음
	// 종료후 first로 이동  -> int형이라 잡음
	// 예외 처리후 first부터 진행
	// thorw가 되는 순간 예외를 빨리 전달하기위해 함수를 끝까지 
	// 진행하지 않고 맞는 형태의 catch를 찾는다.

	cout << "End last" << endl;
}

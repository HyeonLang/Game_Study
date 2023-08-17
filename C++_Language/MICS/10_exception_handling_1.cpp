// 10_exception_handling_1.cpp
/*
	예외처리
	try, catch, throw
*/
#include<iostream>
using namespace std;



int main()
{
	double x;
	cin >> x;


	// try : 예외가 발생할 수 있는 지역을 표시한다.
	try {
		// throw : 예외를 던지고 try 지역을 벗어난다.
		// 아래에 catch에서 예외를 받아 처리 해준다.
		// 만약 catch에서 예외를 받지 못할 경우 에러 발생.
		if (x < 0.0) throw - 1.0; // throw 한 값을 밑 try 코드를 생략하고 catch에서 받음

		if (x >= 100) throw "100이상의 값이 입력됨.";

		cout << sqrt(x) << endl;
	}
	// catch : throw한 예외를 받아 처리한다.
	// throw한 *타입과 일치*해야 catch할 수 있다. 업캐스팅을 제외하고 무조건 일치해야 한다.
	catch (double x) { // throw 받음
		cerr << x << endl; // cerr : 콘솔 에러 메세지 출력
	}
	// catch를 여러개 작성하여 다양한 타입으로 throw하고 catch할 수 있다.
	// 상수 데이터를 참조 형태로 받는 경우에는 const 잘 맞춰줘야 한다.
	catch (const char* error_message) { // string => const char* : 문자열 상수는 수정할 수 없음.
		cerr << error_message << endl;
	}
	return 0;
}
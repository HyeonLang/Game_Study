// 08_string.cpp

#include<iostream>
#include<string>

using namespace std;

int main()
{
	// 포인터로 문자열 상수를 받게되면 문자열 상수의 원본 주소를 받기 때문에
	// 데이터를 수정할 수 없는 형태로 받아야만 한다.
	const char* test = "Hello";

	// 원본 데이터를 복사하는 사본 데이터를 만들기 때문에 const를 추가하지
	// 않아도 가능
	char my_str[] = "Hello, C++";

	// string : 문자열을 다루기 쉽게 해주는 객체
	string str = "Hello, C++!";

	// 길이반환
	str.size();
	str.length();
	
	// 변수처럼 초기화 가능
	string a("Hello, ");
	string b("C++!!");

	// + 연산 가능
	string c = a + b;

	c += ", good!!";
	cout << c << endl;

	// 배열처럼 사용가능
	c[0];


	return 0;
}
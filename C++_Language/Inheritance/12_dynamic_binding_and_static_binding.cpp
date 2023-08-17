// 12_dynamic_binding_and_static_binding.cpp
// 동적 바인딩과 정적 바인딩

/*
	Binding - 바인딩
		- 프로그램 소스에 쓰인 각종 내부요소, 이름, 식별자들에 대해 값 또는 속성을 확정해주는 과정
		- 함수가 호출될 때 함수의 주소를 연결해주는 것

	Static Binding (Early Binding) - 정적 바인딩
		- 컴파일 타임 때 이미 결정
		- 빠른 속도, 유연하지 않다.

	Dynamic Binding (Late Binding) - 동적 바인딩
		- 런 타임 때 이미 결정
		- 느린 속도, 유연 하다.
*/

#include<iostream>
using namespace std;

int add(int x, int y) { return x + y; }
int subract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }

int main()
{
	int x, y;
	cin >> x >> y;

	int op;
	cout << "0 : add, 1 : subtract, 2 : multiply" << endl;
	cin >> op;

	// 정적 바인딩

	int result;
	switch (op)
	{
	// 일반적인 함수 호출
	case 0: result = add(x, y); break;
	case 1: result = subract(x, y); break;
	case 2: result = multiply(x, y); break;
	default: cout << "Invalid parameter" << endl; break;
	}

	cout << result << endl;


	// 동적 바인딩

	int(*func_ptr)(int, int) = nullptr; // 함수 포인터

	switch (op)
	{
	// 함수 포인터에 함수 대입
	case 0: func_ptr = add; break;
	case 1: func_ptr = subract; break;
	case 2: func_ptr = multiply; break;
	default: cout << "Invalid parameter" << endl; break;
	}

	cout << func_ptr(x, y) << endl; // 함수 호출 시점

	return 0;
}
// 06_type_inference.cpp
// 타입 추론

/*
	auto
	- 초기화하는 값에 따라서 데이터타입을 자동으로 정리해주는 키워드
*/

#include<iostream>

// 매개변수는 auto 키워드 x
//int add(auto x, auto y);

auto add(int x, int y)
{
	return x + y;
}

using namespace std;

int main()
{
	int a = 10;
	float f = 3.14f;
	double d = 45.0;

	auto result = d + f;

	return 0;
}
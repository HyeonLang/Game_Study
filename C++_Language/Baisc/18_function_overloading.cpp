// 18_function_overloading.cpp
/*
	함수의 매개변수를 다르게 하여 
	같은 이름의 함수를 중복(적재)하여 사용.
*/

#include <iostream>

int add(int a, int b) {
	return a + b;
}

int add(int a) {
	return a + 1;
}

int add(int a, int b, int c) {
	return a + b + c;
}

float add(float a, float b) { 
	return a + b;
}

/*
//같은 타입을 같은 개수로 받는 함수가 있어 정의부로 구분 불가
int add(int a, int b) { 
	return a + b + 10;
}

//같은 타입을 같은 개수로 받는 함수가 있어 반환형으로 구분 불가
void add(int a, int b) {}

//컴파일러가 보기에 integer는 같은 int 이기때문에 구분 불가
using integer = int;
integer add(integer a, integer b) {
	return a + b;
}
*/

void output(unsigned int value) {}
void output(float value) {}

int main() {
	using namespace std;

	auto result1 = add(10, 20);
	auto result2 = add(10.0f, 20.0f);

	cout << result1 << ", " << result2 << endl;

	output(1.1f);
	output(10u);
	//output(10); //묵시적 형변환 모호성 문제 : ambiguous
	return 0;
}
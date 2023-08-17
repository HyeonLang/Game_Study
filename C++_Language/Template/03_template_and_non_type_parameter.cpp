// 03_template_and_non_type_parameter.cpp
// 템플릿과 자료형이 아닌 매개변수

#include <iostream>
#include <array>
using namespace std;

/*
	non-type parameter : 자료형이 아닌 템플릿 매개변수
	- 자료형이 아닌 상수값을 넣어준다
*/

template<class T, unsigned int SIZE> // non_type_parameter
class MyArray {
public:
	MyArray() = default;
	~MyArray() = default;
private:
	T arr1[10];
	T arr2[SIZE]; // 템플릿 구체화 시점(컴파일 타임) 때 SIZE가 매크로 상수처럼 동작
};

int main() {
	array<int, 10> stl_arr; // 10 : non_type_parameter (변수 안됨)

	MyArray<int, 10> arr1;
	MyArray<double, 10> arr2;

}

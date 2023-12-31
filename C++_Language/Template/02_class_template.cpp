// 02_class_template.cpp

#include <iostream>
#include "02_my_arr.h"

//#include "02_my_arr.cpp" // 해결방법 2.

using namespace std;

int main() {
	MyArray<int> my_array1(10);
	my_array1.Print();

	MyArray<double> my_array2(10);
	my_array2.Print();

	return 0;
}

/*
	클래스 템플릿 코드를 작성할 때 멤버 함수의 선언부와 정의부를 분리하면 링크에러가 발생한다.


	※이유※
	
	템플릿 코드는 함수를 정의한 것이 아니라 함수의 정의를 생성하기 위해 작성된 틀이다.
	
	템플릿 코드는 컴파일 타임 때 구체화가 된다. 
		-> 특정 데이터형 함수가 필요하면 컴파일러가 틀을 보고 작성.
	
	컴파일 타임에서 컴파일러가 작성해주기 때문에 컴파일러가 해당 함수의 템플릿 정의부를 알아야한다.
		-> 컴파일러가 작성하는 시점에 템플릿이 제공되어야 작성이 가능

	만약 정의부가 헤더와 분리되어 있다면 해당 헤더를 포함한 소스 파일에서는 함수의 정의부를
	작성하지 못하므로 정의부 작성이 제대로 안되며 링크 타임에서 함수를 찾지 못해 에러가 발생한다.

	
	※해결 방법※

	1. 정의부를 .h 에 같이 작성 (일반적)
	2. 헤더 추가시 .h와 같이 정의부를 넣어둔 .cpp도 같이 추가한다. (이론상만 가능하며 하지 않는다.)
	3. .inl 파일을 만들어 관리한다. (헤더가 길어질 경우)

*/
// 09_typename_and_nested_dependent_type_name.cpp
// 타입 이름과 중첩 의존 타입 이름

#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
	using my_int = int; // 중첩 타입
};

template<typename T>
class B
{
public:

	/*
		템플릿 내부에서 중첩 의존 타입 이름을 사용할 때 typename을 사용해야 한다.

		dependent - 의존 이름
		- 위의 <typename T>처럼 타입을 인자로 받아 사용할 때 T를 의존 이름이라고 부른다.

		nested dependent type name - 중첩 의존 타입 이름
		- 의존 이름속에 다른 타입이 정의된 경우에 중첩 의존 타입 이름이라고 부른다.
			-> EX) T::my_int
	*/

	//T::my_int i;

	typename T::my_int i; // 타입임을 명시 : 중첩 의존 타입 이름
	
};

int main() {

	B<A> test;

	return 0;
}
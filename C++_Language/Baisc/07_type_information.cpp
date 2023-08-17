// 07_type_information.cpp

/*
	RTTI - Run Time Type Information
	- 런타임 중에 실시간으로 데이터 타입에 대한 정보를 얻는 기능
	- 이게 켜저있어야 typeid()사용해 자료형을 제대로 읽는다.
	- dynamic_cast를 사용할때도 필요하다.
	- 런타임때 자료형을 읽어오는거라 느리다.
*/

/*
	과제 RTTI 조사
*/

#include<iostream>
#include<typeinfo> // typeid

//int add(int a, int b) { return a + b; }
//short add(short a, short b) { return a + b; }
//float add(float a, float b) { return a + b; }

template<typename T>
T add(T a, T b)
{
	std::cout << "a : " << typeid(a).name() << std::endl;
	std::cout << "b : " << typeid(b).name() << std::endl;

	return a + b;
}

int main()
{
	add<int>(10, 20);
	add<float>(10, 20);

	return 0;
}
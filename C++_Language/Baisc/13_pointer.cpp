// 13_pointer.cpp
#include<iostream>

int main()
{
	NULL; //일반 변수에만 사용

	0; //NULL
	(void*)0; //nullptr

	int* ptr = nullptr; // c++에서는 NULL안씀
	int* ptr2(nullptr);
	int* ptr2{ nullptr };

	const char* str = "DiDi"; //const 필수



	return 0;
}
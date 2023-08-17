// 03_variable.cpp

#include<iostream>
#include<numeric>

int main()
{
	/*
		Initialziation
	*/

	int x = 10;		// copy
	int y(10);		// direct
	int z{ 10 };	// uniform : 안전하게 데이터 초기화 가능

	int a = 1.1;
	//int b{1.1};		// error, 작은 형으로 캐스팅되어 데이터가 손실
	char c = 500;
	//char d{500};		// error, 오버 플로우가 일어나 데이터 손실

	/*
		limits
		- 각각의 자료형의 한계값을 가지고 있는 클래스
	*/

	// <> : template
	std::cout << std::numeric_limits<short>::max() << std::endl;
	std::cout << std::numeric_limits<int>::min() << std::endl;
	std::cout << std::numeric_limits<int>::max() << std::endl;
	std::cout << std::numeric_limits<float>::min() << std::endl;
	std::cout << std::numeric_limits<float>::max() << std::endl << std::endl;

	/*
		Casting
	*/
	float k = 10.0f;

	std::cout << k << std::endl;
	std::cout << (int)k << std::endl; // c style 너무 강력함 -> 관계없는 자료형끼리의 형변환도 가능함
	std::cout << int(k) << std::endl; // c++ style 너무 강력함 -> 관계없는 자료형끼리의 형변환도 가능함
	std::cout << static_cast<int>(k) << std::endl;


	// 과제 : cast 종류 4가지 조사
	// - static_cast
	// - reinterpret_cast
	// - dynamic_cast
	// - const_cast


	/*
		const vs constexpr
	*/

	/*
		const
		- 초기화하는 값에 따라 런타임이나 컴파일 타임때 값이 정해진다.
	*/

	// 리터럴 상수(컴파일 타임때 확정된 값)으로 초기화하는 경우 컴파일 타임때 정해짐 
	const int c1(123);

	int i1 = 10;
	// 변수(런타임때 결정되는 값)으로 초기화하는 경우 런타임때 정해짐
	const int c2 = i1;

	int arr_1[c1];
	//int arr_2[c2];

	/*
		constexpr
		- 컴파일 타임때 정해진다
		- 매크로와 비슷하지만 디버깅이 가능하다.
	*/

	constexpr float pi1 = 3.141592f;

	float pi2 = 3.141592f;
	//constexpr float pi3 = pi2; // error : 변수는 컴파일 시점에 값을 알 수 없어 넣어줄 수 없음

	return 0;
}